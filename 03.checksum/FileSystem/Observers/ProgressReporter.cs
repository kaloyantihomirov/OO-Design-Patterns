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

        private long elapsedMs = 0;

        private TimeSpan GetElapsed()
        {
            return TimeSpan.FromMilliseconds(elapsedMs + sw.ElapsedMilliseconds);
        }

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

                    currentFile = fileName;
                    currFileProcessedBytes = 0;
                    break;
                case long chunkBytesSoFar:
                    Thread.Sleep(10);

                    var delta = chunkBytesSoFar - currFileProcessedBytes;
                    currFileProcessedBytes = chunkBytesSoFar;
                    bytesProcessedSoFar += delta;

                    var elapsed = GetElapsed();
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

                case AllFilesProcessedMsg _:
                    Console.WriteLine();
                    break;

                case UserHasRequestedPauseAfterCurrFileProcessedMsg pauseAfterCurrFileProcessed:
                    sw.Stop();
                    FillMementoWithMyValues(pauseAfterCurrFileProcessed.Memento);
                    Console.WriteLine();
                    break;
            }
        }

        public void FillMementoWithMyValues(SharedMemento sm)
        {
            //return new ProgressReporterMemento(bytesProcessedSoFar, bytesToProcess, GetElapsed().Milliseconds);
            sm.ElapsedMilliseconds = elapsedMs;
            sm.BytesProcessedSoFar = bytesProcessedSoFar;
            sm.BytesToProcess = bytesToProcess;
        }

        public void RestoreFromMemento(SharedMemento memento)
        {
            currentFile = "(none)";
            bytesProcessedSoFar = memento.BytesProcessedSoFar;
            bytesToProcess = memento.BytesToProcess;
            currFileProcessedBytes = 0;
            elapsedMs = memento.ElapsedMilliseconds;
            sw.Reset();
            sw.Start();
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