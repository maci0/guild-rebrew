/* Ghidra script: disassemble and create functions at addresses from file.
 *
 * Reads addresses from function_addresses.txt (one hex address per line),
 * disassembles at each address if needed, then creates a function.
 * This fixes "No instruction at address" errors from rebrew sync --push.
 *
 * Run via: Ghidra Script Manager (Window > Script Manager > Run)
 *
 * @category rebrew
 */

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.program.model.address.AddressSet;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;

public class DisassembleAndCreateFunctions extends GhidraScript {
    @Override
    public void run() throws Exception {
        File addrFile = new File(
            "/home/maci/ghidra_scripts/function_addresses.txt");

        if (!addrFile.exists()) {
            println("ERROR: " + addrFile.getAbsolutePath() + " not found");
            return;
        }

        ArrayList<String> addresses = new ArrayList<>();
        BufferedReader reader = new BufferedReader(new FileReader(addrFile));
        String line;
        while ((line = reader.readLine()) != null) {
            line = line.trim();
            if (!line.isEmpty() && !line.startsWith("#")) {
                addresses.add(line);
            }
        }
        reader.close();

        println("Processing " + addresses.size() + " addresses...");

        int disassembled = 0;
        int created = 0;
        int alreadyExist = 0;
        int failed = 0;

        for (String addrStr : addresses) {
            if (monitor.isCancelled()) {
                println("Cancelled by user.");
                break;
            }

            Address addr;
            try {
                /* Strip 0x prefix if present */
                String hex = addrStr.startsWith("0x") ? addrStr.substring(2) : addrStr;
                addr = currentProgram.getAddressFactory()
                    .getDefaultAddressSpace().getAddress(hex);
            } catch (Exception e) {
                println("  SKIP invalid address: " + addrStr + " (" + e.getMessage() + ")");
                failed++;
                continue;
            }

            /* Check if function already exists at this address */
            Function existing = currentProgram.getFunctionManager().getFunctionAt(addr);
            if (existing != null) {
                alreadyExist++;
                continue;
            }

            /* Check if there's an instruction; if not, disassemble */
            Instruction instr = currentProgram.getListing().getInstructionAt(addr);
            if (instr == null) {
                /* Try to disassemble */
                DisassembleCommand cmd = new DisassembleCommand(
                    new AddressSet(addr), null, true);
                boolean ok = cmd.applyTo(currentProgram, monitor);
                if (ok) {
                    instr = currentProgram.getListing().getInstructionAt(addr);
                }
                if (instr == null) {
                    println("  FAIL disassemble at " + addrStr);
                    failed++;
                    continue;
                }
                disassembled++;
            }

            /* Create function */
            try {
                Function func = createFunction(addr, null);
                if (func != null) {
                    created++;
                } else {
                    println("  FAIL createFunction at " + addrStr + " (returned null)");
                    failed++;
                }
            } catch (Exception e) {
                println("  FAIL createFunction at " + addrStr + ": " + e.getMessage());
                failed++;
            }
        }

        println("Done.");
        println("  Already existed: " + alreadyExist);
        println("  Disassembled:    " + disassembled);
        println("  Created:         " + created);
        println("  Failed:          " + failed);
        println("  Total processed: " + addresses.size());
    }
}
