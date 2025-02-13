using _03.checksum.Checksum;
using _03.checksum.FileSystem;
using _03.checksum.FileSystem.ChecksumFormatter;
using _03.checksum.FileSystem.Observers;

namespace _03.checksum
{
    public class Program
    {

        [STAThread]
        public static void Main(string[] args)
        {
            DirectoryEntry de = DirectoryEntryHelper.BuildRootDirectoryEntryInMem("C:\\Users\\kkolev\\Downloads\\Junction", false);

            using StreamWriter sw = new StreamWriter(Console.OpenStandardOutput());

            ProgressReporter po = new ProgressReporter(de.GetSizeInBytes());

            PauseManager pm = new PauseManager();

            HashStreamWriter hsw = new HashStreamWriter(new Md5Calculator(), sw, new XmlChecksumFormatter());
            pm.RegisterObserver(hsw);
            hsw.RegisterObserver(po);

            Caretaker caretaker = new Caretaker(hsw, po);
            hsw.RegisterObserver(caretaker);
            po.RegisterObserver(caretaker);

            Thread scanThread = new Thread(() =>
            {
                hsw.VisitDirectory(de);
            });
            scanThread.Start();

            ConsoleKeyInfo key = new ConsoleKeyInfo();

            while (!Console.KeyAvailable && key.Key != ConsoleKey.Escape)
            {
                key = Console.ReadKey(true);

                switch (key.Key)
                {
                    case ConsoleKey.P:
                        pm.RequestPause();
                        break;
                    case ConsoleKey.S:
                        pm.RequestResume();
                        caretaker.Restore();
                        if (!scanThread.IsAlive)
                        {
                            scanThread = new Thread(() =>
                            {
                                hsw.VisitDirectory(de);
                            });
                            scanThread.Start();
                        }
                        break;
                }
            }


        }
    }
}
