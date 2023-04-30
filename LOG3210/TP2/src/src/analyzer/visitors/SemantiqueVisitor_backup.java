//package analyzer.visitors;
//
//import analyzer.SemantiqueError;
//import analyzer.ast.*;
//
//import java.io.PrintWriter;
//import java.util.ArrayList;
//import java.util.HashMap;
//import java.util.List;
//import java.util.Objects;
//
///**
// * Created: 19-01-10
// * Last Changed: 03-02-23
// * Author: Félix Brunet
// * <p>
// * Description: Ce visiteur explorer l'AST est renvois des erreurs lorsqu'une erreur sémantique est détectée.
// */
//
//public class SemantiqueVisitor_backup implements ParserVisitor {
//
//    private final PrintWriter m_writer;
//
//    private HashMap<String, VarType> SymbolTable = new HashMap<>(); // mapping variable -> type
//
//    // variable pour les metrics
//    public int VAR = 0;
//    public int WHILE = 0;
//    public int IF = 0;
//    public int FUNC = 0;
//    public int OP = 0;
//
//    public SemantiqueVisitor_backup(PrintWriter writer) {
//        m_writer = writer;
//    }
//
//    /*
//    IMPORTANT:
//    *
//    * L'implémentation des visiteurs se base sur la grammaire fournie (Langage.jjt). Il faut donc la consulter pour
//    * déterminer les noeuds enfants à visiter. Cela vous sera utile pour lancer les erreurs au bon moment.
//    * Pour chaque noeud, on peut :
//    *   1. Déterminer le nombre d'enfants d'un noeud : jjtGetNumChildren()
//    *   2. Visiter tous les noeuds enfants: childrenAccept()
//    *   3. Accéder à un noeud enfant : jjtGetChild()
//    *   4. Visiter un noeud enfant : jjtAccept()
//    *   5. Accéder à m_value (type) ou m_ops (vecteur des opérateurs) selon la classe de noeud AST (src/analyser/ast)
//    *
//    * Cela permet d'analyser l'intégralité de l'arbre de syntaxe abstraite (AST) et d'effectuer une analyse sémantique du code.
//    *
//    * Le Visiteur doit lancer des erreurs lorsqu'une situation arrive.
//    *
//    * Pour vous aider, voici le code à utiliser pour lancer les erreurs :
//    *
//    * - Utilisation d'identifiant non défini :
//    *   throw new SemantiqueError("Invalid use of undefined Identifier " + node.getValue());
//    *
//    * - Plusieurs déclarations pour un identifiant. Ex : num a = 1; bool a = true; :
//    *   throw new SemantiqueError(String.format("Identifier %s has multiple declarations", varName));
//    *
//    * - Utilisation d'un type num dans la condition d'un if ou d'un while :
//    *   throw new SemantiqueError("Invalid type in condition");
//    *
//    * - Utilisation de types non valides pour des opérations de comparaison :
//    *   throw new SemantiqueError("Invalid type in expression");
//    *
//    * - Assignation d'une valeur à une variable qui a déjà reçu une valeur d'un autre type. Ex : a = 1; a = true; :
//    *   throw new SemantiqueError(String.format("Invalid type in assignation of Identifier %s", varName));
//    *
//    * - Le type de retour ne correspond pas au type de fonction :
//    *   throw new SemantiqueError("Return type does not match function type");
//    * */
//
//
//    @Override
//    public Object visit(SimpleNode node, Object data) {
//        return data;
//    }
//
//    @Override
//    public Object visit(ASTProgram node, Object data) {
//        node.childrenAccept(this, data);
//        m_writer.print(String.format("{VAR:%d, WHILE:%d, IF:%d, FUNC:%d, OP:%d}", this.VAR, this.WHILE, this.IF, this.FUNC, this.OP));
//        return null;
//    }
//
//    // Enregistre les variables avec leur type dans la table symbolique.
//    @Override
//    public Object visit(ASTDeclaration node, Object data) {
//        String varName = ((ASTIdentifier) node.jjtGetChild(0)).getValue();
//        // TODO
//        if(this.SymbolTable.get(varName) == null) {
//            VarType type;
//
//            if(Objects.equals(node.getValue(), "num")) {
//                type = VarType.Number;
//            } else type = VarType.Bool;
//            SymbolTable.put(varName, type);
//            this.VAR++;
//        } else {
//            throw new SemantiqueError("Identifier " + varName + " has multiple declarations");
//        }
//        return null;
//    }
//
//    @Override
//    public Object visit(ASTBlock node, Object data) {
//        node.childrenAccept(this, data);
//        return null;
//    }
//
//    @Override
//    public Object visit(ASTStmt node, Object data) {
//        node.childrenAccept(this, data);
//        return null;
//    }
//
//    // Méthode qui pourrait être utile pour vérifier le type d'expression dans une condition.
//    private void callChildenCond(SimpleNode node) {
//        DataStruct d = new DataStruct();
//        node.jjtGetChild(0).jjtAccept(this, d);
//
//        // TODO
//
//        int numChildren = node.jjtGetNumChildren();
//        for (int i = 1; i < numChildren; i++) {
//            d = new DataStruct();
//            node.jjtGetChild(i).jjtAccept(this, d);
//        }
//    }
//
//    // les structures conditionnelle doivent vérifier que leur expression de condition est de type booléenne
//    // On doit aussi compter les conditions dans les variables IF et WHILE
//    @Override
//    public Object visit(ASTIfStmt node, Object data) {
//        // TODO : Fiez vous aux langages pour determiner les noeuds enfants possible
//        this.IF++;
//        return null;
//    }
//
//    @Override
//    public Object visit(ASTWhileStmt node, Object data) {
//        // TODO
//        this.WHILE++;
//        return null;
//    }
//
//    @Override
//    public Object visit(ASTFunctionStmt node, Object data) {
//        // TODO
//        this.FUNC++;
//        return null;
//    }
//
//    @Override
//    public Object visit(ASTFunctionBlock node, Object data) {
//        // TODO
//        return null;
//    }
//
//    @Override
//    public Object visit(ASTReturnStmt node, Object data) {
//        // TODO
//        return null;
//    }
//
//    // On doit vérifier que le type de la variable est compatible avec celui de l'expression.
//    @Override
//    public Object visit(ASTAssignStmt node, Object data) {
//        // TODO
//        DataStruct child = new DataStruct();
//        node.childrenAccept(this, child);
//        String varName = ((ASTIdentifier) node.jjtGetChild(0)).getValue();
//        VarType expected = SymbolTable.get(varName);
//        VarType actual = child.type;
//
//        if(!SymbolTable.containsKey(varName)) {
//            throw new SemantiqueError(String.format("Invalid use of undefined Identifier %s",varName));
//        }
//
//        if(!expected.equals(actual)) {
//            throw new SemantiqueError(String.format("Invalid type in assignation of Identifier %s... was expecting %s but got %s", varName, expected, actual));
//        }
//
//        return null;
//    }
//
//    @Override
//    public Object visit(ASTExpr node, Object data) {
//        // TODO
//        DataStruct childData = new DataStruct();
//        node.childrenAccept(this, childData);
//        if(data!=null){
//            ((DataStruct)data).type = childData.type;
//        }
//        return null;
//    }
//
//    @Override
//    public Object visit(ASTCompExpr node, Object data) {
//        /*
//            Attention, ce noeud est plus complexe que les autres :
//            - S’il n'a qu'un seul enfant, le noeud a pour type le type de son enfant.
//            - S’il a plus d'un enfant, alors il s'agit d'une comparaison. Il a donc pour type "Bool".
//            - Il n'est pas acceptable de faire des comparaisons de booléen avec les opérateurs < > <= >=.
//            - Les opérateurs == et != peuvent être utilisé pour les nombres et les booléens, mais il faut que le type
//            soit le même des deux côtés de l'égalité/l'inégalité.
//        */
//        // TODO
//
//        List<VarType> types = new ArrayList<>();
//
//        for (int i = 0; i < node.jjtGetNumChildren(); i++) {
//            DataStruct childData = new DataStruct();
//            node.jjtGetChild(i).jjtAccept(this, childData);
//            types.add(childData.type);
//        }
//
//        if(node.jjtGetNumChildren()==1) {
//            ((DataStruct) data).type = types.get(0);
//        } else if(node.jjtGetNumChildren()>1){
//            OP++;
//            ((DataStruct)data).type = VarType.Bool;
//            boolean containsEquals = node.getValue().equals("==");
//            boolean containsNotEquals = node.getValue().equals("!=");
//            boolean containsLesser = node.getValue().equals("<");
//            boolean containsGreater = node.getValue().equals(">");
//            boolean containsLesserOrEqual = node.getValue().equals("<=");
//            boolean containsGreaterOrEqual = node.getValue().equals(">=");
//            boolean leftISBool = types.get(0).equals(VarType.Bool);
//            boolean RightIsBool = types.get(1).equals(VarType.Bool);
//            boolean sameTypesOnBothSides = types.get(0).equals(types.get(1));
//
//
//            if(!containsEquals && !containsNotEquals && !containsLesser && !containsGreater && !containsLesserOrEqual && !containsGreaterOrEqual ||
//                    !containsEquals && !containsNotEquals && leftISBool || !containsEquals && !containsNotEquals && RightIsBool || !sameTypesOnBothSides){
//                throw  new SemantiqueError("Invalid type in expression");
//            }
//        }
//
//        return null;
//    }
//
//
//    /*
//        Opérateur binaire :
//        - s’il n'y a qu'un enfant, aucune vérification à faire.
//        - Par exemple, un AddExpr peut retourner le type "Bool" à condition de n'avoir qu'un seul enfant.
//     */
//    @Override
//    public Object visit(ASTAddExpr node, Object data) {
//        // TODO
//        List<VarType> types = new ArrayList<VarType>();
//        int numChildren = node.jjtGetNumChildren();
//        for (int i = 0; i < numChildren; i++) {
//            DataStruct d = new DataStruct();
//            node.jjtGetChild(i).jjtAccept(this, d);
//            ((DataStruct)data).type = d.type;
//            if(node.getOps().size()>0 && d.type != null){
//                types.add(d.type);
//            }
//        }
//
//        return null;
//    }
//
//    @Override
//    public Object visit(ASTMulExpr node, Object data) {
//        // TODO
//        int numChildren = node.jjtGetNumChildren();
//        for (int i = 0; i < numChildren; i++) {
//            DataStruct d = new DataStruct();
//            node.jjtGetChild(i).jjtAccept(this, d);
//        }
//        return null;
//    }
//
//    @Override
//    public Object visit(ASTBoolExpr node, Object data) {
//        // TODO
//        int numChildren = node.jjtGetNumChildren();
//        for (int i = 0; i < numChildren; i++) {
//            DataStruct d = new DataStruct();
//            node.jjtGetChild(i).jjtAccept(this, d);
//
//        }
//        return null;
//    }
//
//    /*
//        Opérateur unaire
//        Les opérateurs unaires ont toujours un seul enfant. Cependant, ASTNotExpr et ASTUnaExpr ont la fonction
//        "getOps()" qui retourne un vecteur contenant l'image (représentation str) de chaque token associé au noeud.
//        Il est utile de vérifier la longueur de ce vecteur pour savoir si un opérande est présent.
//        - S’il n'y a pas d'opérande, ne rien faire.
//        - S’il y a un (ou plus) opérande, il faut vérifier le type.
//    */
//    @Override
//    public Object visit(ASTNotExpr node, Object data) {
//        // TODO
//        this.OP++;
//        return null;
//    }
//
//    @Override
//    public Object visit(ASTUnaExpr node, Object data) {
//        // TODO
//        this.OP++;
//        return null;
//    }
//
//    /*
//        Les noeud ASTIdentifier ayant comme parent "GenValue" doivent vérifier leur type.
//        On peut envoyer une information à un enfant avec le 2e paramètre de jjtAccept ou childrenAccept.
//     */
//    @Override
//    public Object visit(ASTGenValue node, Object data) {
//        node.childrenAccept(this, data);
//        return null;
//    }
//
//
//    @Override
//    public Object visit(ASTBoolValue node, Object data) {
//        ((DataStruct) data).type = VarType.Bool;
//        return null;
//    }
//
//    @Override
//    public Object visit(ASTIdentifier node, Object data) {
//
//        if (node.jjtGetParent() instanceof ASTGenValue) {
//            String varName = node.getValue();
//            VarType varType = SymbolTable.get(varName);
//
//            ((DataStruct) data).type = varType;
//        }
//
//        return null;
//    }
//
//    @Override
//    public Object visit(ASTIntValue node, Object data) {
//        ((DataStruct) data).type = VarType.Number;
//        return null;
//    }
//
//
//    //des outils pour vous simplifier la vie et vous enligner dans le travail
//    public enum VarType {
//        Bool,
//        Number
//    }
//
//
//    private class DataStruct {
//        public VarType type;
//
//        public DataStruct() {
//        }
//
//        public DataStruct(VarType p_type) {
//            type = p_type;
//        }
//
//    }
//}
