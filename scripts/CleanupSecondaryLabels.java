/* Ghidra script: delete secondary LABEL-type symbols at function entry points.
 *
 * These were created by rebrew sync --push using create-label, which cannot
 * override FUNCTION-type primary symbols. The leftover LABEL symbols block
 * set-function-prototype (DuplicateNameException).
 *
 * Run via: Ghidra Script Manager (Window > Script Manager > Run)
 *
 * @category rebrew
 */

import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolTable;
import ghidra.program.model.symbol.SymbolType;
import ghidra.program.model.address.Address;
import java.util.ArrayList;

public class CleanupSecondaryLabels extends GhidraScript {
    @Override
    public void run() throws Exception {
        SymbolTable st = currentProgram.getSymbolTable();
        FunctionIterator funcIter = currentProgram.getFunctionManager().getFunctions(true);

        int deleted = 0;
        while (funcIter.hasNext()) {
            Function func = funcIter.next();
            Address addr = func.getEntryPoint();

            ArrayList<Symbol> toDelete = new ArrayList<>();
            for (Symbol sym : st.getSymbols(addr)) {
                if (sym.getSymbolType() == SymbolType.LABEL) {
                    toDelete.add(sym);
                }
            }
            for (Symbol sym : toDelete) {
                String name = sym.getName();
                sym.delete();
                deleted++;
                println("Deleted LABEL '" + name + "' at " + addr);
            }
        }

        println("Done. Deleted " + deleted + " secondary labels.");
    }
}
