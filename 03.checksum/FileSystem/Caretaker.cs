using _03.checksum.FileSystem.Observers;

namespace _03.checksum.FileSystem;

//public class Caretaker : IObserver
//{
//    private readonly HashStreamWriter hashStreamWriter;
//    private readonly ProgressReporter progressReporter;

//    public Caretaker(
//        HashStreamWriter hashStreamWriter, 
//        ProgressReporter progressReporter)
//    {
//        this.hashStreamWriter = hashStreamWriter;
//        this.progressReporter = progressReporter;
//    }

//    public HashStreamWriterMemento HashStreamWriterMemento { get; set; }
//    public ProgressReporterMemento ProgressReporterMemento { get; set; }

//    public void Update(ISubject sender, object message)
//    {
//        if (message is HashStreamWriterMemento hswm)
//        {
//            HashStreamWriterMemento = hswm;
//        }
//        else if (message is ProgressReporterMemento prm)
//        {
//            ProgressReporterMemento = prm;
//        }
//    }

//    public void Restore()
//    {
//        if (HashStreamWriterMemento == null)
//        {
//            return;
//        }

//        hashStreamWriter.RestoreFromMemento(HashStreamWriterMemento);
//        progressReporter.RestoreFromMemento(ProgressReporterMemento);
//    }

//}