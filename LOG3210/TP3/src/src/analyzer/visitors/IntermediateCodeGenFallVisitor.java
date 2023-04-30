package analyzer.visitors;

import analyzer.ast.*;

import java.io.PrintWriter;


/**
 * Ce visiteur explore l'AST et génère du code intermédiaire.
 *
 * @author Félix Brunet
 * @author Doriane Olewicki
 * @author Quentin Guidée
 * @version 2023.02.17
 */
public class IntermediateCodeGenFallVisitor extends IntermediateCodeGenVisitor implements ParserVisitor {
    public static final String FALL = "fall";
    private final PrintWriter m_writer;

    public IntermediateCodeGenFallVisitor(PrintWriter writer) {
        super(writer);
        m_writer = writer;
    }

    @Override
    public Object visit(SimpleNode node, Object data) {
        return data;
    }

    @Override
    public Object visit(ASTIfStmt node, Object data) {
        BoolLabel b = new BoolLabel(FALL, data.toString());

        if (node.jjtGetNumChildren() == 2) {
            node.jjtGetChild(0).jjtAccept(this, b);
            node.jjtGetChild(1).jjtAccept(this, data);

        } else {
            b.lFalse = newLabel();
            node.jjtGetChild(0).jjtAccept(this, b);
            node.jjtGetChild(1).jjtAccept(this, data);
            m_writer.println(String.format("goto %s", data));
            m_writer.println(String.format("%s", b.lFalse));
            node.jjtGetChild(2).jjtAccept(this, data);
        }
        return null;
    }

    @Override
    public Object visit(ASTWhileStmt node, Object data) {
        String begin = newLabel();
        BoolLabel b = new BoolLabel(FALL, data.toString());

        m_writer.println(String.format("%s", begin));

        node.jjtGetChild(0).jjtAccept(this, b);
        node.jjtGetChild(1).jjtAccept(this, begin);

        m_writer.println(String.format("goto %s", begin));

        return null;
    }

    @Override
    public Object visit(ASTAssignStmt node, Object data) {
        String identifier = ((ASTIdentifier) node.jjtGetChild(0)).getValue();

        if (super.SymbolTable.get(identifier).equals(VarType.Bool)) {
            BoolLabel newLabel = new BoolLabel(FALL, newLabel());
            node.jjtGetChild(1).jjtAccept(this, newLabel);
            m_writer.print(String.format("%s = 1\ngoto %s\n%s\n%s = 0\n", identifier, data.toString(), newLabel.lFalse, identifier));

        } else {
            String test = node.jjtGetChild(1).jjtAccept(this, null).toString();
            m_writer.println(identifier + " = " + test);
        }
        return null;
    }

    @Override
    public Object visit(ASTBoolExpr node, Object data) {
        if (node.jjtGetNumChildren() == 1)
            return node.jjtGetChild(0).jjtAccept(this, data);

        String op = node.getOps().get(0).toString();
        if (op.equals("&&")) {
            BoolLabel b1 = new BoolLabel(FALL, ((BoolLabel) data).lFalse);

            if (b1.lFalse.equals(FALL))
                b1.lFalse = newLabel();

            BoolLabel b2 = new BoolLabel(((BoolLabel) data).lTrue, ((BoolLabel) data).lFalse);

            if (((BoolLabel) data).lFalse.equals(FALL)) {
                node.jjtGetChild(0).jjtAccept(this, b1);
                node.jjtGetChild(1).jjtAccept(this, b2);
                m_writer.println(b1.lFalse);

            } else {
                node.jjtGetChild(0).jjtAccept(this, b1);
                node.jjtGetChild(1).jjtAccept(this, b2);
            }

        } else if (op.equals("||")) {
            BoolLabel b1 = new BoolLabel(((BoolLabel) data).lTrue, FALL);

            if (((BoolLabel) data).lTrue.equals(FALL))
                b1.lTrue = newLabel();

            BoolLabel b2 = new BoolLabel(((BoolLabel) data).lTrue, ((BoolLabel) data).lFalse);

            if (((BoolLabel) data).lTrue.equals(FALL)) {
                node.jjtGetChild(0).jjtAccept(this, b1);
                node.jjtGetChild(1).jjtAccept(this, b2);
                m_writer.println(b1.lTrue);

            } else {
                node.jjtGetChild(0).jjtAccept(this, b1);
                node.jjtGetChild(1).jjtAccept(this, b2);
            }
        }
        return null;
    }

    @Override
    public Object visit(ASTCompExpr node, Object data) {
        if (node.jjtGetNumChildren() == 1)
            return node.jjtGetChild(0).jjtAccept(this, data);

        BoolLabel b = (BoolLabel) data;

        if (!b.lTrue.equals(FALL) && !b.lFalse.equals(FALL)) {
            String id1 = node.jjtGetChild(0).jjtAccept(this, data).toString();
            String id2 = node.jjtGetChild(1).jjtAccept(this, data).toString();
            m_writer.println(String.format("if %s %s %s goto %s", id1, node.getValue(), id2, b.lTrue));
            m_writer.println(String.format("goto %s", b.lFalse));

        } else if (!b.lTrue.equals(FALL) && b.lFalse.equals(FALL)) {
            String id1 = node.jjtGetChild(0).jjtAccept(this, data).toString();
            String id2 = node.jjtGetChild(1).jjtAccept(this, data).toString();
            m_writer.println(String.format("if %s %s %s goto %s", id1, node.getValue(), id2, b.lTrue));

        } else if (b.lTrue.equals(FALL) && !b.lFalse.equals(FALL)) {
            String id1 = node.jjtGetChild(0).jjtAccept(this, data).toString();
            String id2 = node.jjtGetChild(1).jjtAccept(this, data).toString();
            m_writer.println(String.format("ifFalse %s %s %s goto %s", id1, node.getValue(), id2, b.lFalse));
        }
        return null;
    }

    @Override
    public Object visit(ASTBoolValue node, Object data) {
        BoolLabel label = (BoolLabel) data;

        if (node.getValue()) {
            if (!label.lTrue.equals(FALL))
                m_writer.println(String.format("goto %s", label.lTrue));
        } else {
            if (!label.lFalse.equals(FALL))
                m_writer.println(String.format("goto %s", label.lFalse));
        }

        return node.getValue();
    }

    @Override
    public Object visit(ASTIdentifier node, Object data) {
        BoolLabel b = ((BoolLabel) data);

        if (super.SymbolTable.get(node.getValue()) == VarType.Bool) {

            if (!b.lTrue.equals(FALL) && !b.lFalse.equals(FALL)) {
                m_writer.println(String.format("if %s == 1 goto %s", node.getValue(), b.lTrue));
                m_writer.println(String.format("goto %s", b.lFalse));

            } else if (!b.lTrue.equals(FALL) && b.lFalse.equals(FALL)) {
                m_writer.println(String.format("if %s == 1 goto %s", node.getValue(), b.lTrue));

            } else if (b.lTrue.equals(FALL) && !b.lFalse.equals(FALL)) {
                m_writer.println(String.format("ifFalse %s == 1 goto %s", node.getValue(), b.lFalse));
            }
        }
        return node.getValue();
    }
}
