using System.Diagnostics;

namespace _03.checksum.FileSystem.Observers
{
    public class ProgressReporter : IObserver, ISubject
    {
        private string currentFile = "(none)";
        private long bytesProcessedSoFar = 0;
        private long bytesToProcess = 0;
        private long currFileProcessedBytes = 0;
        private Stopwatch sw;

        private readonly List<IObserver> observers = new List<IObserver>();

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
                    if (fileName == "PAUSE") return;
                    if (fileName == "PAUSE_FINISHED_FILE_PROCESSING")
                    {
                        ProgressReporterMemento prm = CreateMemento();
                        NotifyObservers(prm);
                        return;
                    }

                    if(currentFile != "(none)") Console.WriteLine();
                    if (fileName == "END")
                    {
                        sw.Stop();
                        Console.Write("\n");
                    }
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
                    //Console.WriteLine($"\n[DEBUG] Unknown message type: {message?.GetType().Name} from {sender.GetType().Name}");
                    //throw new ArgumentException($"Unknown message type: {message?.GetType().Name} from {sender.GetType().Name}");
                    break;
            }
        }

        public ProgressReporterMemento CreateMemento()
        {
            return new ProgressReporterMemento("(none)", bytesProcessedSoFar, bytesToProcess, currFileProcessedBytes, sw.ElapsedMilliseconds);
        }

        public void RestoreFromMemento(ProgressReporterMemento memento)
        {
            currentFile = memento.CurrentFile;
            bytesProcessedSoFar = memento.BytesProcessedSoFar;
            bytesToProcess = memento.BytesToProcess;
            currFileProcessedBytes = 0;
        }

        public void RegisterObserver(IObserver observer)
        {
            this.observers.Add(observer);
        }

        public void RemoveObserver(IObserver observer)
        {
            this.observers.Remove(observer);
        }

        public void NotifyObservers(object message)
        {
            foreach (var observer in observers)
            {
                observer.Update(this, message);
            }
        }
    }
}