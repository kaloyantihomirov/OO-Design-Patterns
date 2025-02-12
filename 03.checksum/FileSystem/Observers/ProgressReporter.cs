using System.Diagnostics;

namespace _03.checksum.FileSystem.Observers
{
    public class ProgressReporter : IObserver
    {
        private string currentFile = "(none)";
        private long bytesProcessedSoFar = 0;
        private long bytesToProcess = 0;
        private long currFileProcessedBytes = 0;
        private Stopwatch sw;

        public ProgressReporter(long bytesToProcess)
        {
            this.bytesToProcess = bytesToProcess;
            sw = Stopwatch.StartNew();
        }

        public void Update(ISubject sender, object message)
        {
            switch (message)
            {
                case string fileName:
                    if(currentFile != "(none)") Console.WriteLine();
                    if(currentFile == "END") sw.Stop();
                    currentFile = fileName;
                    currFileProcessedBytes = 0;
                    break;
                case long chunkBytesSoFar:
                    Thread.Sleep(10);

                    var delta = chunkBytesSoFar - currFileProcessedBytes;
                    currFileProcessedBytes = chunkBytesSoFar;
                    bytesProcessedSoFar += delta;

                    var elapsed = sw.Elapsed;
                    double bytesPerSecond = bytesProcessedSoFar / elapsed.TotalSeconds;
                    double percent = (double)bytesProcessedSoFar / bytesToProcess * 100.0;
                    double remainingBytes = bytesToProcess - bytesProcessedSoFar;

                    double estimatedSecRemaining = (bytesPerSecond > 0)
                        ? remainingBytes / bytesPerSecond
                        : 0;

                    Console.Write(
                        $"\rProcessing {currentFile}... {chunkBytesSoFar} byte(s) read " +
                        $"| {percent:F2}% " +
                        $"| ETA: {TimeSpan.FromSeconds(estimatedSecRemaining):hh\\:mm\\:ss\\.fff}"
                    );

                    break;
                default:
                    Console.WriteLine($"\n[DEBUG] Unknown message type: {message?.GetType().Name} from {sender.GetType().Name}");
                    break;
            }
        }

    }
}