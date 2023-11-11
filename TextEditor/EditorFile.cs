using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace TextEditor
{
    internal class EditorFile
    {
        private static Regex fileRegex = new Regex(@"^(.*[\\\/])([^\\\/]+)\.([^.]+)$");
        private string _filePath;
        private string _fileName;
        private string _fileExtension;

        public EditorFile(string path)
        {
            if (!File.Exists(path)) { throw new ArgumentException("file doesn't exist"); }
            Match match = fileRegex.Match(path);
            if (!match.Success) { throw new ArgumentException("not a valid path"); }
            _filePath = match.Groups[1].Value;
            _fileName = match.Groups[2].Value;
            _fileExtension = match.Groups[3].Value;
        }
        // make this work I guess
        private const string namePattern = @"^(?!(?:PRN|AUX|CLOCK\$|NUL|CON|COM\d|LPT\d)(?:\..+)?$)[^\x00-\x1F\xA5\\?*:\"";|\/<>]+(?<![\s.])$";
        private static Regex nameRegex = new Regex(namePattern, RegexOptions.IgnoreCase);

        public bool UpdateName(string name) // returns true if name updated
        {
            if (!nameRegex.IsMatch(name)) { return false; }
            _fileName = name;
            return true;
        }

        public string GetPath()
        {
            return String.Concat(_filePath, _fileName, _fileExtension);
        }
    }
}
