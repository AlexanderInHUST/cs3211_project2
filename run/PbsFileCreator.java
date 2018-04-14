import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;

/**
 * Created by tangyifeng on 2018/4/13.
 * Email: yifengtang_hust@outlook.com
 */
public class PbsFileCreator {

    private final static String seqNamePrefix = "seq";
    private final static String parNamePrefix = "par";

    public static void createSeqPbsScripts() {
        for (int i = 1; i <= 4; i++) {
            for (int j = 1; j <= 100000; j *= 10) {
                try {
                    String fileName = seqNamePrefix + "_" + i + "X" + i + "_" + j + ".pbs";
                    File script = new File(fileName);
                    PrintWriter writer = new PrintWriter(new FileOutputStream(script));
                    writer.println("#!/bin/bash");
                    writer.println("#PBS -l select=1:ncpus=1:mem=4G");
                    writer.println("#PBS -l walltime=23:59:59");
                    writer.println("#PBS -P Personal");
                    writer.println("#PBS -N " + fileName);
                    writer.println("#PBS -o /home/users/nus/e0271033/galaxy_simulation/" + fileName + "_out");
                    writer.println("#PBS -e /home/users/nus/e0271033/galaxy_simulation/" + fileName + "_out");
                    writer.println("cd $PBS_O_WORKDIR/../");
                    writer.println("mkdir " + fileName + "_out");
                    writer.println("./simulation.seq input_" + j + ".in " + fileName + "_out/result " + i * i);
                    writer.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static void createParPbsScripts() {
        for (int i = 1; i <= 4; i++) {
            for (int j = 1; j <= 100000; j *= 10) {
                try {
                    String fileName = parNamePrefix + "_" + i + "X" + i + "_" + j + ".pbs";
                    File script = new File(fileName);
                    PrintWriter writer = new PrintWriter(new FileOutputStream(script));
                    writer.println("#!/bin/bash");
                    writer.println("#PBS -l select=1:ncpus=" + i * i + ":mem=4G:mpiprocs=" + i * i);
                    writer.println("#PBS -l walltime=23:59:59");
                    writer.println("#PBS -P Personal");
                    writer.println("#PBS -N " + fileName);
                    writer.println("#PBS -o /home/users/nus/e0271033/galaxy_simulation/" + fileName + "_out");
                    writer.println("#PBS -e /home/users/nus/e0271033/galaxy_simulation/" + fileName + "_out");
                    writer.println("module load openmpi");
                    writer.println("cd $PBS_O_WORKDIR/../");
                    writer.println("mkdir " + fileName + "_out");
                    writer.println("mpirun -np " + i * i + " ./simulation.par input_" + j + ".in " + fileName + "_out/result");
                    writer.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static void main(String[] args) {
        createSeqPbsScripts();
        createParPbsScripts();
    }
}
