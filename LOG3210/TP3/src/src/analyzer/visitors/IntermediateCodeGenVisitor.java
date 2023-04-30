package analyzer.visitors;

import analyzer.ast.*;

import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.Vector;


/**
 * Ce visiteur explore l'AST et génère du code intermédiaire.
 *
 * @author Félix Brunet
 * @author Doriane Olewicki
 * @author Quentin Guidée
 * @version 2023.02.17
 */
public class IntermediateCodeGenVisitor implements ParserVisitor {
    private final PrintWriter m_writer;

    public HashMap<String, VarType> SymbolTable = new HashMap<>();

    protected int id = 0;
    protected int label = 0;

    public IntermediateCodeGenVisitor(PrintWriter writer) {
        m_writer = writer;
    }

    protected String newID() {
        return "_t" + id++;
    }

    protected String newLabel() {
        return "_L" + label++;
    }

    @Override
    public Object visit(SimpleNode node, Object data) {
        return data;
    }

    @Override
    public Object visit(ASTProgram node, Object data) { // P --> S

        // TODO
        String next = newLabel();
        node.childrenAccept(this, next);
        m_writer.println(next);
        return null;
    }

    @Override
    public Object visit(ASTDeclaration node, Object data) {
        ASTIdentifier id = (ASTIdentifier) node.jjtGetChild(0);
        SymbolTable.put(id.getValue(), node.getValue().equals("bool") ? VarType.Bool : VarType.Number);
        return null;
    }

    @Override
    public Object visit(ASTBlock node, Object data) {
        for (int i = 0; i < node.jjtGetNumChildren() - 1; i++) {
            String nextI = newLabel();
            node.jjtGetChild(i).jjtAccept(this, nextI);
            m_writer.println(nextI);
        }
        node.jjtGetChild(node.jjtGetNumChildren() - 1).jjtAccept(this, data);
        // TODO
        return null;
    }

    @Override
    public Object visit(ASTScriptProgram node, Object data) {
        ArrayList<String> scriptCalls = new ArrayList<>((Collection<String>) node.jjtGetChild(node.jjtGetNumChildren() - 1).jjtAccept(this, data));

        for (String scriptCall : scriptCalls) {
            for (int j = 0; j < node.jjtGetNumChildren() - 1; j++) {
                if (scriptCall.equals(((ASTScript) node.jjtGetChild(j)).getValue())) {
                    node.jjtGetChild(j).jjtAccept(this, data);
                }
            }
        }
        return null;
    }

    @Override
    public Object visit(ASTScript node, Object data) {
        node.childrenAccept(this, data);
        return null;
    }

    @Override
    public Object visit(ASTScriptCall node, Object data) {
        ArrayList<String> scriptCalls = new ArrayList<>();
        scriptCalls.add(((ASTIdentifier) node.jjtGetChild(0)).getValue());
        if (node.jjtGetNumChildren() > 1)
            scriptCalls.addAll((Collection<String>) node.jjtGetChild(1).jjtAccept(this, data));
        return scriptCalls;
    }

    @Override
    public Object visit(ASTStmt node, Object data) {
        node.childrenAccept(this, data);
        return null;
    }

    @Override
    public Object visit(ASTIfStmt node, Object data) {
        // TODO
        if (node.jjtGetNumChildren() <= 2) {
            String B_true = newLabel();
            String B_false = data.toString();
            BoolLabel B_bool_label = new BoolLabel(B_true, B_false);
            String S1_next = data.toString();
            node.jjtGetChild(0).jjtAccept(this, B_bool_label);
            m_writer.println(B_true);
            node.jjtGetChild(1).jjtAccept(this, S1_next);
        } else {
            String B_true = newLabel();
            String B_false = newLabel();
            BoolLabel B_bool_label = new BoolLabel(B_true, B_false);
            String S1_next = data.toString();
            String S2_next = data.toString();
            node.jjtGetChild(0).jjtAccept(this, B_bool_label);
            m_writer.println(B_true);
            node.jjtGetChild(1).jjtAccept(this, S1_next);
            m_writer.println("goto " + S1_next);
            m_writer.println(B_false);
            node.jjtGetChild(2).jjtAccept(this, S2_next);
        }
        return null;
    }

    @Override
    public Object visit(ASTWhileStmt node, Object data) {
        // TODO
        String begin = newLabel();
        String B_true = newLabel();
        String B_false = data.toString();
        BoolLabel B_bool_label = new BoolLabel(B_true, B_false);
        m_writer.println(begin);
        node.jjtGetChild(0).jjtAccept(this, B_bool_label);
        m_writer.println(B_true);
        node.jjtGetChild(1).jjtAccept(this, begin);
        m_writer.println("goto " + begin);
        return null;
    }

    @Override
    public Object visit(ASTForStmt node, Object data) {
        // TODO


        String begin = newLabel();
        String end = newLabel();
        String B_true = newLabel();
        String B_false = data.toString();
        BoolLabel B_bool_label = new BoolLabel(B_true, B_false);
        node.jjtGetChild(0).jjtAccept(this, data);
        m_writer.println(begin);
        node.jjtGetChild(1).jjtAccept(this, B_bool_label);
        m_writer.println(B_true);
        node.jjtGetChild(3).jjtAccept(this, end);
        m_writer.println(end);
        node.jjtGetChild(2).jjtAccept(this, data);
        m_writer.println("goto " + begin);

        return null;
    }

    @Override
    public Object visit(ASTAssignStmt node, Object data) { // S --> id = E

        String identifier = ((ASTIdentifier) node.jjtGetChild(0)).getValue();
        if (SymbolTable.get(identifier).equals(VarType.Bool)) {
            String B_true_label = newLabel(); // B.true = newlabel()
            String B_false_label = newLabel(); // B.false = newlabel()
            BoolLabel bool_label = new BoolLabel(B_true_label, B_false_label); // B.true = newlabel() et B.false = newlabel()
            node.jjtGetChild(1).jjtAccept(this, bool_label);
            m_writer.println(B_true_label);
            m_writer.println(identifier + " = 1");
            m_writer.println("goto " + data);
            m_writer.println(B_false_label);
            m_writer.println(identifier + " = 0");
        }
        if (SymbolTable.get(identifier).equals(VarType.Number)) {
            String addr = node.jjtGetChild(1).jjtAccept(this, data).toString();
            m_writer.println(identifier + " = " + addr);
        }
        // TODO
        // visit E
        return null;
    }

    @Override
    public Object visit(ASTExpr node, Object data) {
        return node.jjtGetChild(0).jjtAccept(this, data);
    }

    public Object codeExtAddMul(SimpleNode node, Object data, Vector<String> ops) {
        // À noter qu'il n'est pas nécessaire de boucler sur tous les enfants.
        // La grammaire n'accepte plus que 2 enfants maximum pour certaines opérations, au lieu de plusieurs
        // dans les TPs précédents. Vous pouvez vérifier au cas par cas dans le fichier Langage.jjt.
        // TODO
        if (ops.size() == 0) return node.jjtGetChild(0).jjtAccept(this, data); // pour tout sauf + et -
        // E → E1 + E2
        String temp = newID(); // new Temp()
        String addr_E1 = node.jjtGetChild(0).jjtAccept(this, data).toString(); // E1.code
        String addr_E2 = node.jjtGetChild(1).jjtAccept(this, data).toString(); // E2.code
        m_writer.println(temp + " = " + addr_E1 + " " + ops.get(0) + " " + addr_E2); // gen(E.addr′ =′ E1.addr′ +′ E2.addr)
        return temp;
    }

    @Override
    public Object visit(ASTAddExpr node, Object data) {
        return codeExtAddMul(node, data, node.getOps());
    }

    @Override
    public Object visit(ASTMulExpr node, Object data) {
        return codeExtAddMul(node, data, node.getOps());
    }

    @Override
    public Object visit(ASTUnaExpr node, Object data) {
        if (node.getOps().size() == 0) return node.jjtGetChild(0).jjtAccept(this, data);
        String addr_E1 = node.jjtGetChild(0).jjtAccept(this, data).toString(); // E1.code
        String final_temp = "";
        for (int i = 0; i < node.getOps().size(); i++) {
            String temp = newID(); // new Temp()
            m_writer.println(temp + " = - " + addr_E1); // gen(E.addr′ =′′ minus′E1.addr)
            addr_E1 = temp;
            if (i == node.getOps().size() - 1) final_temp = temp;
        }
        // TODO
        return final_temp;
    }

    @Override
    public Object visit(ASTBoolExpr node, Object data) {
        // node.childrenAccept(this, data);
        // TODO
        if (node.getOps().size() == 0) return node.jjtGetChild(0).jjtAccept(this, data);
        if (node.getOps().toString().equals("[&&]")) {
            String B1_true_label = newLabel();
            String B1_false_label = ((BoolLabel) data).lFalse;
            String B2_true_label = ((BoolLabel) data).lTrue;
            String B2_false_label = ((BoolLabel) data).lFalse;
            BoolLabel B1_bool_label = new BoolLabel(B1_true_label, B1_false_label);
            BoolLabel B2_bool_label = new BoolLabel(B2_true_label, B2_false_label);
            node.jjtGetChild(0).jjtAccept(this, B1_bool_label);
            m_writer.println(B1_true_label);
            node.jjtGetChild(1).jjtAccept(this, B2_bool_label);
        }
        if (node.getOps().toString().equals("[||]")) {
            String B1_true_label = ((BoolLabel) data).lTrue;
            String B1_false_label = newLabel();
            String B2_true_label = ((BoolLabel) data).lTrue;
            String B2_false_label = ((BoolLabel) data).lFalse;
            BoolLabel B1_bool_label = new BoolLabel(B1_true_label, B1_false_label);
            BoolLabel B2_bool_label = new BoolLabel(B2_true_label, B2_false_label);
            node.jjtGetChild(0).jjtAccept(this, B1_bool_label);
            m_writer.println(B1_false_label);
            node.jjtGetChild(1).jjtAccept(this, B2_bool_label);
        }
        return null;
    }

    @Override
    public Object visit(ASTCompExpr node, Object data) {
        // TODO
        if (node.getValue() == null) return node.jjtGetChild(0).jjtAccept(this, data);
        String E1_addr = node.jjtGetChild(0).jjtAccept(this, data).toString();
        String E2_addr = node.jjtGetChild(1).jjtAccept(this, data).toString();
        m_writer.println("if " + E1_addr + " " + node.getValue() + " " + E2_addr + " goto " + ((BoolLabel) data).lTrue);
        m_writer.println("goto " + ((BoolLabel) data).lFalse);
        return null;
    }

    @Override
    public Object visit(ASTNotExpr node, Object data) {
        // TODO
        if (node.getOps().size() % 2 == 0) return node.jjtGetChild(0).jjtAccept(this, data);
        String B1_true_label = ((BoolLabel) data).lFalse;
        String B1_false_label = ((BoolLabel) data).lTrue;
        BoolLabel B1_bool_label = new BoolLabel(B1_true_label, B1_false_label);
        return node.jjtGetChild(0).jjtAccept(this, B1_bool_label);
    }

    @Override
    public Object visit(ASTGenValue node, Object data) {
        // TODO
        return node.jjtGetChild(0).jjtAccept(this, data);
    }

    @Override
    public Object visit(ASTBoolValue node, Object data) {
        // TODO
        if (node.getValue().toString().equals("true")) {
            m_writer.println("goto " + ((BoolLabel) data).lTrue);
        }
        if (node.getValue().toString().equals("false")) {
            m_writer.println("goto " + ((BoolLabel) data).lFalse);
        }
        return null;
    }

    @Override
    public Object visit(ASTIdentifier node, Object data) { // E --> id ou B --> id
        // TODO
        if (SymbolTable.get(node.getValue()) == VarType.Bool) {
            m_writer.println("if " + node.getValue() + " == 1 goto " + ((BoolLabel) data).lTrue);
            m_writer.println("goto " + ((BoolLabel) data).lFalse);
        }
        return node.getValue();
    }

    @Override
    public Object visit(ASTIntValue node, Object data) {
        return Integer.toString(node.getValue());
    }

    public enum VarType {
        Bool,
        Number
    }

    protected static class BoolLabel {
        public String lTrue;
        public String lFalse;

        public BoolLabel(String lTrue, String lFalse) {
            this.lTrue = lTrue;
            this.lFalse = lFalse;
        }
    }
}
