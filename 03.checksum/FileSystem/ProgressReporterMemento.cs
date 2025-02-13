namespace _03.checksum.FileSystem;

public class ProgressReporterMemento
{
    public ProgressReporterMemento(
        long bytesProcessedSoFar,
        long bytesToProcess,
        long elapsedMilliseconds)
    {
        BytesProcessedSoFar = bytesProcessedSoFar;
        BytesToProcess = bytesToProcess;
        ElapsedMilliseconds = elapsedMilliseconds;
    }

    public long BytesProcessedSoFar { get; }

    public long BytesToProcess { get; }

    public long ElapsedMilliseconds { get; }
}