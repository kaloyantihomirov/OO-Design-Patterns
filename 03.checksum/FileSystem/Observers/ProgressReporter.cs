namespace _03.checksum.FileSystem.Observers
{
    public class ProgressReporter : IObserver
    {
        private string currentFile = "(none)";
        private long bytesReadSoFar = 0;

        public void Update(ISubject sender, object message)
        {
            switch (message)
            {
                case string fileName:
                    if(currentFile != "(none)") Console.WriteLine();
                    currentFile = fileName;
                    bytesReadSoFar = 0;
                    break;
                case long chunkBytesSoFar:
                    bytesReadSoFar = chunkBytesSoFar;
                    Thread.Sleep(10);
                    Console.Write($"\rProcessing {currentFile}... {bytesReadSoFar} byte(s) read");
                    break;
                default:
                    Console.WriteLine($"\n[DEBUG] Unknown message type: {message?.GetType().Name} from {sender.GetType().Name}");
                    break;
            }
        }

    }
}