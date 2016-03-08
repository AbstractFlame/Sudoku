using System;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

namespace Sudoku3000
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();

            sudokuDataGridView.Paint += new PaintEventHandler(GridPaint); // a blokkok szegélyezéséhez
            NewTable();
        }

        private void GridPaint(object sender, PaintEventArgs e)
        {
            Graphics graphics = e.Graphics;
            if (sudokuDataGridView.RowCount == 9)
            {
                int step = (int)Math.Sqrt((double)sudokuDataGridView.RowCount);
                for (int i = 0; i < sudokuDataGridView.RowCount; i = i + step)
                    for (int j = 0; j < sudokuDataGridView.ColumnCount; j = j + step)
                    {
                        DataGridViewCell cell = sudokuDataGridView.Rows[i].Cells[j];
                        graphics.DrawRectangle(Pens.Black, new Rectangle(i * cell.Size.Width,
                                                                        j * cell.Size.Height + 2,
                                                                        cell.Size.Width * step - 1,
                                                                        cell.Size.Height * step - 2));
                    }
            }
            else
            {
                int width = sudokuDataGridView.Size.Width/2 - 1;
                int height = sudokuDataGridView.Size.Height/2;
                graphics.DrawRectangle(Pens.Black, new Rectangle(2, 2, width, height));
                graphics.DrawRectangle(Pens.Black, new Rectangle(width, 2, width, height));
                graphics.DrawRectangle(Pens.Black, new Rectangle(2, height, width, height));
                graphics.DrawRectangle(Pens.Black, new Rectangle(width, height, width, height));
            }
        }

        private void initializeTable()
        {
            for (int i = 0; i < solutionDataGridView.RowCount; i++)
            {
                sudokuDataGridView.Columns.RemoveAt(i);
                sudokuDataGridView.Rows.RemoveAt(i);
                solutionDataGridView.Columns.RemoveAt(i);
                solutionDataGridView.Rows.RemoveAt(i);
            }
            
            sudokuDataGridView.ColumnCount = Program.size;
            sudokuDataGridView.RowCount = Program.size;
            solutionDataGridView.ColumnCount = Program.size;
            solutionDataGridView.RowCount = Program.size;
        }

        // cellák tartalmának középre igazítása és a sormagasság beállítása
        private void formatTable()
        {
            for (int i = 0; i < Program.size; i++)
            {
                sudokuDataGridView.DefaultCellStyle.Alignment = DataGridViewContentAlignment.MiddleCenter;
                sudokuDataGridView.Rows[i].Height = sudokuDataGridView.Size.Height/Program.size;
                solutionDataGridView.DefaultCellStyle.Alignment = DataGridViewContentAlignment.MiddleCenter;
                solutionDataGridView.Rows[i].Height = sudokuDataGridView.Size.Height/Program.size;
            }
        }

        // Meghívjuk a c++-ban elkészített Sudoku.exe állományt, ami legenerálja számunkra a sudoku táblát, amit ki is ír a
        // szabványos kimenetre, ahonnan ez a program leolvassa
        private string getSudokuString()
        {
            Process generatorProgram = new Process();
            generatorProgram.StartInfo.FileName = Application.StartupPath + "\\Sudoku.exe";
            ProcessStartInfo myProcessStartInfo = new ProcessStartInfo(Application.StartupPath + "\\Sudoku.exe", "Sudoku generator");
            myProcessStartInfo.UseShellExecute = false;
            myProcessStartInfo.RedirectStandardOutput = true;
            myProcessStartInfo.WindowStyle = ProcessWindowStyle.Hidden; // fusson a háttérben
            generatorProgram.StartInfo = myProcessStartInfo;
            generatorProgram.StartInfo.Arguments = Program.size + " " + Program.unFilledCells;
            generatorProgram.Start();
            StreamReader reader = generatorProgram.StandardOutput; // eredmény kiolvasása a szabványos kimenetről
            generatorProgram.WaitForExit();
            if (generatorProgram.ExitCode != 0)
            {
                MessageBox.Show("A program futása során hiba történt. A program nem tudta legenerálni a sudoku tábla számait.");
                generatorProgram.Close();
                Environment.Exit(1);
                return "";
            }
            generatorProgram.Close();
            
            return reader.ReadToEnd();
        }

        // a console program kimenetének (sudoku tábla) eredmény feldolgozása
        private void fillSudokuTable(String sudokuOutput)
        {
            int iIndex;
            int c = 0;
            int size = Program.size * Program.size;
            for (; c < size; c++)
            {
                iIndex = (int)Math.Ceiling((double)(c + 1) / Program.size) - 1;
                Program.table[iIndex, c % Program.size] = (int)Char.GetNumericValue(sudokuOutput[c]);
            }
            for (; c < size * 2; c++)
            {
                iIndex = (int)Math.Ceiling((double)(c + 1 - size) / Program.size) - 1;
                Program.tableMap[iIndex, c % Program.size] = Char.GetNumericValue(sudokuOutput[c]) == 0.0 ? false : true;
            }
        }

        // táblázat kirajzolása
        private void fillGrid()
        {
            sudokuDataGridView.DefaultCellStyle.BackColor = Color.White;
            sudokuDataGridView.DefaultCellStyle.SelectionBackColor = Color.WhiteSmoke;
            for (int i = 0; i < sudokuDataGridView.RowCount; i++)
                for (int j = 0; j < sudokuDataGridView.ColumnCount; j++)
                {
                    if(Program.tableMap[i, j]) {
                        sudokuDataGridView.Rows[i].Cells[j].Value = Program.table[i, j].ToString();
                        sudokuDataGridView.Rows[i].Cells[j].Style.ForeColor = Color.DarkRed;
                    }
                    else
                        sudokuDataGridView.Rows[i].Cells[j].Value = "";
                    sudokuDataGridView.Rows[i].Cells[j].Style.BackColor = Color.White;
                    sudokuDataGridView.Rows[i].Cells[j].Style.SelectionBackColor = Color.WhiteSmoke;
                }
        }

        private void NewTable()
        {
            Program.closed = false;

            solutionDataGridView.Visible = false; // eltüntetjük a megoldástáblát

            initializeTable();
            formatTable();
            String output = getSudokuString();
            fillSudokuTable(output);
            fillGrid();
        }

        private void settingsButton_Click(object sender, EventArgs e)
        {
            SettingsForm settingsForm = new SettingsForm();
            settingsForm.ShowDialog(this);
        }

        private void newButton_Click(object sender, EventArgs e)
        {
            NewTable();
        }

        private void sudokuDataGridView_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!Program.closed && 49 <= (int)e.KeyChar && (int)e.KeyChar <= 57 && !Program.tableMap[sudokuDataGridView.CurrentCell.RowIndex, sudokuDataGridView.CurrentCell.ColumnIndex])
                sudokuDataGridView.SelectedCells[0].Value = e.KeyChar;
        }

        private void solutionButton_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < solutionDataGridView.RowCount; i++)
                for (int j = 0; j < solutionDataGridView.ColumnCount; j++)
                    solutionDataGridView.Rows[i].Cells[j].Value = Program.table[i, j];

            solutionDataGridView.Visible = true;
            Program.closed = true;

            bool perfect = true;
            for (int i = 0; i < sudokuDataGridView.RowCount; i++)
                for (int j = 0; j < sudokuDataGridView.ColumnCount; j++)
                {
                    if (sudokuDataGridView.Rows[i].Cells[j].Value.ToString() != solutionDataGridView.Rows[i].Cells[j].Value.ToString())
                    {
                        sudokuDataGridView.Rows[i].Cells[j].Style.BackColor = Color.Red;
                        sudokuDataGridView.Rows[i].Cells[j].Style.SelectionBackColor = Color.Red;
                        perfect = false;
                    }
                    else
                        sudokuDataGridView.Rows[i].Cells[j].Style.SelectionBackColor = Color.White;
                }
            if (perfect)
                MessageBox.Show("Congratulation! Perfect work!");
        }

        private void sudokuDataGridView_CellMouseUp(object sender, DataGridViewCellMouseEventArgs e)
        {
            if (Program.tableMap[sudokuDataGridView.CurrentCell.RowIndex, sudokuDataGridView.CurrentCell.ColumnIndex])
                sudokuDataGridView.CurrentCell.Style.SelectionForeColor = Color.DarkRed;
            else
                sudokuDataGridView.CurrentCell.Style.SelectionForeColor = Color.DimGray;
            
        }
    }
}