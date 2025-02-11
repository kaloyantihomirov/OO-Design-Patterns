using System.Collections.Specialized;
using System.Text;
using System.CommandLine;
using System.CommandLine.Parsing;
using _03.checksum.FileSystem;

namespace _03.checksum
{
    public class Program
    {
        enum SupportedHashAlgo
        {
            Md5,
            Sha1
        }

        enum SupportedOutputFormat
        {
            Text,
            Json
        }

        [STAThread]
        public static void Main(string[] args)
        {
            //dotnet run -- -path "text.txt" -algorithm "md5" --follow-symbolic-links 
            // var c = new RootCommand();

            // var checkSum = new Option<string?>("--checksum", () => null,
            //     "Verify checksums.")
            // {
            //     Arity = ArgumentArity.ExactlyOne
            // };

            // var path = new Option<string>("--path", "Path to a file/directory to work on.")
            // {
            //     Arity = ArgumentArity.ExactlyOne
            // };
            // path.SetDefaultValue(Directory.GetCurrentDirectory());

            // var algoName = new Option<SupportedHashAlgo>("--algorithm", "Algorithm to use to hash.")
            // {
            //     Arity = ArgumentArity.ExactlyOne
            // };
            // algoName.SetDefaultValue(SupportedHashAlgo.Md5);

            // var followSymbolicLinks = new Option<bool>("--follow-symbolic-links",
            //     "Traverse the target of the symbolic link or shortcut.")
            // {
            //     Arity = ArgumentArity.Zero
            // };

            // var outputFormat = new Option<SupportedOutputFormat>("--output-format", "Output format to use.")
            // {
            //     Arity = ArgumentArity.ExactlyOne
            // };
            // outputFormat.SetDefaultValue(SupportedOutputFormat.Text);

            // c.Add(path);
            // c.Add(algoName);
            // c.Add(outputFormat);
            // c.Add(followSymbolicLinks);

            // c.SetHandler((p,  algo,  followLinks, outFormat) =>
            // {
            //     Console.WriteLine(p);
            // }, 
            //     path,
            //     algoName,
            //     followSymbolicLinks,
            //     outputFormat);

            // c.Invoke(args);

            // Md5Calculator md5Calculator = new Md5Calculator();
            // IChecksumCalculator sha1Calculator = new Sha1Calculator();

            // using FileStream fs = File.OpenRead("text.txt");

            // //string checksum = md5Calculator.Calculate(fs);
            // string checksum2 = sha1Calculator.Calculate(fs);
            //// Console.WriteLine(checksum);
            // Console.WriteLine(checksum2);


            //FileInfo pathInfo = new FileInfo(@"C:\Users\kkolev\Desktop\sample.txt");

            //string path = @"C:\Users\kkolev\Desktop\test\HP - Shortcut (2).lnk";

            //Console.WriteLine(
            //    ShortcutHelper.GetLnkTarget(path));
            //Console.WriteLine(File.Exists(path));

            // DirectoryInfo di = new DirectoryInfo(@"C:\Users\kkolev\desktop\bcserver Command Prompt.lnk");
            // Console.WriteLine(di.LinkTarget);

            IAbstractDirectoryBuilder builder = new SymLinkAwareDirectoryBuilder();
            string directoryPath = @"C:\Users\kkolev\desktop\test";
            builder.StartDirectory(directoryPath);
            DirectoryEntry de = builder.GetResult();

            de.Print();



            //DirectoryEntry de = DirectoryBuildingClient.BuildDirectoryTree(@"C:\Users\kkolev\desktop\messages.csv");

            //de.Print();


            //byte[] b = new byte[1024];
            //UTF8Encoding temp = new UTF8Encoding(true);
            //int readLen;
            //while ((readLen = fs.Read(b, 0, b.Length)) > 0)
            //{
            //    Console.WriteLine(temp.GetString(b, 0, readLen));
            //}
        }
    }
}
