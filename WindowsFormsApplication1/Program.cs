using System;
using System.Windows.Forms;

namespace Sudoku3000
{
    static class Program
    {
        public static int size = 9;  // a tábla mérete (size x size méretű)
        public static int unFilledCells = 30; // a nehézségi szintet jelöli (minél magasabb, annál nehezebb)
        public static int blockSize = (int)Math.Sqrt((double)size); // megállapítjuk a blokkok méretét (blockSize x blockSize)
        public static bool closed; // ha lekértük a megoldást, utána már ne lehessen változtatni a számokon
        public static int[,] table = new int[9, 9]; // a tábla, amibe generáljuk a sudoku számait
        public static bool[,] tableMap = new bool[9, 9]; // logikai tábla, ami megmutatja, hogy a tábla mely elemeit vettük ki, illetve tartottuk meg
        public static bool[,] blockMap = new bool[3, 3]; // az elrejtés során ebben tároljuk azt, hogy ha az adott elrejtendő számot már elrejtettük volna, akkor a blokkjában mely helyeken zárhatjuk ki megjelenését
        public static Random rand = new Random(); // random szám generáláshoz 
        
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new MainForm());
        }
    }
}
