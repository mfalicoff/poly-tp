package analyzer.visitors;

import analyzer.ast.*;

import java.io.PrintWriter;
import java.util.*;

public class PrintMachineCodeVisitor implements ParserVisitor {
    private PrintWriter m_writer = null;

    private int MAX_REGISTERS_COUNT = 256;

    private final ArrayList<String> RETURNS = new ArrayList<>();
    private final ArrayList<MachineCodeLine> CODE = new ArrayList<>();

    private final ArrayList<String> MODIFIED = new ArrayList<>();
    private final ArrayList<String> REGISTERS = new ArrayList<>();

    private final HashMap<String, String> OPERATIONS = new HashMap<>();

    public PrintMachineCodeVisitor(PrintWriter writer) {
        m_writer = writer;

        OPERATIONS.put("+", "ADD");
        OPERATIONS.put("-", "MIN");
        OPERATIONS.put("*", "MUL");
        OPERATIONS.put("/", "DIV");
    }

    @Override
    public Object visit(SimpleNode node, Object data) {
        return null;
    }

    @Override
    public Object visit(ASTProgram node, Object data) {
        node.childrenAccept(this, null);

        computeLifeVar();
        computeNextUse();

        printMachineCode();

        return null;
    }

    @Override
    public Object visit(ASTNumberRegister node, Object data) {
        MAX_REGISTERS_COUNT = ((ASTIntValue) node.jjtGetChild(0)).getValue();
        return null;
    }

    @Override
    public Object visit(ASTReturnStmt node, Object data) {
        for (int i = 0; i < node.jjtGetNumChildren(); i++) {
            RETURNS.add(((ASTIdentifier) node.jjtGetChild(i)).getValue());
        }
        return null;
    }

    @Override
    public Object visit(ASTBlock node, Object data) {
        node.childrenAccept(this, null);
        return null;
    }

    @Override
    public Object visit(ASTStmt node, Object data) {
        node.childrenAccept(this, null);
        return null;
    }

    @Override
    public Object visit(ASTAssignStmt node, Object data) {
        // TODO (ex1): Modify CODE to add the needed MachLine.
        // Here the type of Assignment is "assigned = left op right".
        // You can pass null as data to children.
        String operation = node.getOp();
        String assign = node.jjtGetChild(0).jjtAccept(this, data).toString();
        String exp1 = node.jjtGetChild(1).jjtAccept(this, data).toString();
        String exp2 = node.jjtGetChild(2).jjtAccept(this, data).toString();
        CODE.add(new MachineCodeLine(operation, assign, exp1,exp2));
        return null;
    }

    @Override
    public Object visit(ASTAssignUnaryStmt node, Object data) {
        // TODO (ex1): Modify CODE to add the needed MachLine.
        // Here the type of Assignment is "assigned = - right".
        // Suppose the left part to be the constant "#O".
        // You can pass null as data to children.
        String assign = node.jjtGetChild(0).jjtAccept(this, data).toString();
        String exp1 = node.jjtGetChild(1).jjtAccept(this, data).toString();
        CODE.add(new MachineCodeLine("-", assign, "#0", exp1));
        return null;
    }

    @Override
    public Object visit(ASTAssignDirectStmt node, Object data) {
        // TODO (ex1): Modify CODE to add the needed MachLine.
        // Here the type of Assignment is "assigned = right".
        // Suppose the left part to be the constant "#O".
        // You can pass null as data to children.
        String assign = node.jjtGetChild(0).jjtAccept(this, data).toString();
        String exp1 = node.jjtGetChild(1).jjtAccept(this, data).toString();
        CODE.add(new MachineCodeLine("+", assign, "#0", exp1));
        return null;
    }

    @Override
    public Object visit(ASTExpr node, Object data) {
        return node.jjtGetChild(0).jjtAccept(this, null);
    }

    @Override
    public Object visit(ASTIntValue node, Object data) {
        return "#" + node.getValue();
    }

    @Override
    public Object visit(ASTIdentifier node, Object data) {
        return node.getValue();
    }

    private void computeLifeVar() {
        // TODO (ex2): Implement life variables algorithm on the CODE array.
        this.CODE.forEach(node -> {
            node.Life_IN = new HashSet<>();
            node.Life_OUT = new HashSet<>();
        });

        this.CODE.get(this.CODE.size() - 1).Life_OUT.addAll(this.RETURNS);
        for (int i = this.CODE.size()-1; i>=0; i--) {
            if (i < this.CODE.size()-1) {
                this.CODE.get(i).Life_OUT.addAll(this.CODE.get(i + 1).Life_IN);
            }

            HashSet<String> tempHashSet = new HashSet<>(this.CODE.get(i).Life_OUT);
            tempHashSet.removeAll(this.CODE.get(i).DEF);
            tempHashSet.addAll(this.CODE.get(i).REF);
            this.CODE.get(i).Life_IN = tempHashSet;
        }

    }

    private void computeNextUse() {
        // TODO (ex3): Implement next-use algorithm on the CODE array.

        for (MachineCodeLine line: CODE) {
            line.Next_IN = new NextUse();
            line.Next_OUT = new NextUse();
        }

        for(int i = CODE.size() -1 ; i >= 0; i--) {

            MachineCodeLine currentLine = CODE.get(i);

            if(i < CODE.size() - 1) {
                currentLine.Next_OUT = (NextUse) CODE.get(i+1).Next_IN.clone();
            }

            for (Map.Entry<String, ArrayList<Integer>> set :
                    CODE.get(i).Next_OUT.nextUse.entrySet()) {

                HashSet<String> def = currentLine.DEF;
                if(!def.contains(set.getKey())){
                    currentLine.Next_IN = (NextUse) currentLine.Next_IN.clone();
                    for(int val: set.getValue()){
                        currentLine.Next_IN.add(set.getKey(), val);
                    }
                }
            }

            for (String s : currentLine.REF) {
                CODE.get(i).Next_IN.add(s, i);
            }

        }
    }

    /**
     * This function should generate the LD and ST when needed.
     */
    public String chooseRegister(String variable, HashSet<String> life, NextUse next, boolean loadIfNotFound) {
        // TODO (ex4): if variable is a constant (starts with '#'), return variable
        if(variable.startsWith("#"))
            return variable;

        // TODO (ex4): if REGISTERS contains variable, return "R" + index
        if(REGISTERS.contains(variable))
            return String.format("R%s", REGISTERS.indexOf(variable));

        // TODO (ex4): if REGISTERS size is not max (< MAX_REGISTERS_COUNT), add variable to REGISTERS and return "R" + index
        if(REGISTERS.size() < MAX_REGISTERS_COUNT) {
            REGISTERS.add(variable);
            if(loadIfNotFound)
                m_writer.println(String.format("LD R%s, %s", REGISTERS.size()-1, variable));
            return String.format("R%s", REGISTERS.size()-1);

        } else {
            // TODO (ex4): if REGISTERS has max size:
            // - put variable in space of an other variable which is not used anymore
            // *or*
            // - put variable in space of variable which as the largest next-use

            String victim = "";
            int maxNextUse = -1;

            for (String reg : REGISTERS) {
                if (!next.nextUse.containsKey(reg)) {
                    victim = reg;
                    break;
                } else {
                    int nextUse = next.nextUse.get(reg).get(0);
                    if (nextUse > maxNextUse) {
                        victim = reg;
                        maxNextUse = nextUse;
                    }
                }
            }

            int idxElementToReplace = REGISTERS.indexOf(victim);

            if(MODIFIED.contains(victim) && life.contains(victim))
                m_writer.println(String.format("ST %s, R%s", victim, idxElementToReplace));

            if (loadIfNotFound)
                m_writer.println(String.format("LD R%s, %s", idxElementToReplace, variable));

            REGISTERS.set(idxElementToReplace, variable);
            return String.format("R%s", idxElementToReplace);
        }
    }

    /**
     * Print the machine code in the output file
     */
    public void printMachineCode() {
        // TODO (ex4): Print the machine code in the output file.
        // You should change the code below.
        for (int i = 0; i < CODE.size(); i++) {
            m_writer.println("// Step " + i);

            MachineCodeLine line = CODE.get(i);

            String left = chooseRegister(line.LEFT, line.Life_IN, line.Next_IN, true);
            String right = chooseRegister(line.RIGHT, line.Life_IN, line.Next_IN, true);
            String assign = chooseRegister(line.ASSIGN, line.Life_OUT, line.Next_OUT, false);

            boolean isAddSubZero = (left.equals("#0") || right.equals("#0")) && (line.OPERATION.equals("ADD") || line.OPERATION.equals("SUB"));
            if (!((assign.equals(left) || assign.equals(right)) && isAddSubZero)) {
                m_writer.println(String.format("%s %s, %s, %s", line.OPERATION, assign, left, right));
            }
            
            MODIFIED.add(MODIFIED.size(), line.ASSIGN);
            m_writer.println(line);
        }

        for (String ret : RETURNS) {
            if (MODIFIED.contains(ret) && REGISTERS.contains(ret))
                m_writer.println(String.format("ST %s, R%s", ret, REGISTERS.indexOf(ret)));
        }

    }

    /**
     * Order a set in alphabetic order
     *
     * @param set The set to order
     * @return The ordered list
     */
    public List<String> orderedSet(Set<String> set) {
        List<String> list = new ArrayList<>(set);
        Collections.sort(list);
        return list;
    }

    /**
     * A class to store and manage next uses.
     */
    private class NextUse {
        public HashMap<String, ArrayList<Integer>> nextUse = new HashMap<>();

        public NextUse() {}

        public NextUse(HashMap<String, ArrayList<Integer>> nextUse) {
            this.nextUse = nextUse;
        }

        public ArrayList<Integer> get(String s) {
            return nextUse.get(s);
        }

        public void add(String s, int i) {
            if (!nextUse.containsKey(s)) {
                nextUse.put(s, new ArrayList<>());
            }
            nextUse.get(s).add(i);
        }

        public String toString() {
            ArrayList<String> items = new ArrayList<>();
            for (String key : orderedSet(nextUse.keySet())) {
                Collections.sort(nextUse.get(key));
                items.add(String.format("%s:%s", key, nextUse.get(key)));
            }
            return String.join(", ", items);
        }

        @Override
        public Object clone() {
            return new NextUse((HashMap<String, ArrayList<Integer>>) nextUse.clone());
        }
    }

    /**
     * A struct to store the data of a machine code line.
     */
    private class MachineCodeLine {
        String OPERATION;
        String ASSIGN;
        String LEFT;
        String RIGHT;

        public HashSet<String> REF = new HashSet<>();
        public HashSet<String> DEF = new HashSet<>();

        public HashSet<String> Life_IN = new HashSet<>();
        public HashSet<String> Life_OUT = new HashSet<>();

        public NextUse Next_IN = new NextUse();
        public NextUse Next_OUT = new NextUse();

        public MachineCodeLine(String operation, String assign, String left, String right) {
            this.OPERATION = OPERATIONS.get(operation);
            this.ASSIGN = assign;
            this.LEFT = left;
            this.RIGHT = right;

            DEF.add(this.ASSIGN);
            if (this.LEFT.charAt(0) != '#')
                REF.add(this.LEFT);
            if (this.RIGHT.charAt(0) != '#')
                REF.add(this.RIGHT);
        }

        @Override
        public String toString() {
            String buffer = "";
            buffer += String.format("// Life_IN  : %s\n", Life_IN);
            buffer += String.format("// Life_OUT : %s\n", Life_OUT);
            buffer += String.format("// Next_IN  : %s\n", Next_IN);
            buffer += String.format("// Next_OUT : %s\n", Next_OUT);
            return buffer;
        }
    }
}
