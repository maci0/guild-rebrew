# Ghidra script: delete secondary LABEL-type symbols at function entry points.
#
# These were created by rebrew sync --push using create-label, which cannot
# override FUNCTION-type primary symbols. The leftover LABEL symbols block
# set-function-prototype (DuplicateNameException).
#
# Run via: Ghidra Script Manager (Window > Script Manager > Run)
# @category rebrew
# @menupath Tools.Rebrew Cleanup Labels

from ghidra.program.model.symbol import SymbolType

fm = currentProgram.getFunctionManager()
st = currentProgram.getSymbolTable()

deleted = 0
func_iter = fm.getFunctions(True)
while func_iter.hasNext():
    func = func_iter.next()
    addr = func.getEntryPoint()
    for sym in st.getSymbols(addr):
        if sym.getSymbolType() == SymbolType.LABEL:
            name = sym.getName()
            sym.delete()
            deleted += 1
            println("Deleted LABEL '{}' at {}".format(name, addr))

println("Done. Deleted {} secondary labels.".format(deleted))
