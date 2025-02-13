namespace _03.checksum.FileSystem;

public class ProgressReporterMemento
{
    public ProgressReporterMemento(
        string currentFile,
        long bytesProcessedSoFar,
        long bytesToProcess,
        long currFileProcessedBytes,
        long elapsedMilliseconds)
    {
        CurrentFile = currentFile;
        BytesProcessedSoFar = bytesProcessedSoFar;
        BytesToProcess = bytesToProcess;
        CurrFileProcessedBytes = currFileProcessedBytes;
        ElapsedMilliseconds = elapsedMilliseconds;
    }

    public string CurrentFile { get; }
    public long BytesProcessedSoFar { get; }
    public long BytesToProcess { get; }
    public long CurrFileProcessedBytes { get; }

    public long ElapsedMilliseconds { get; set; }
}