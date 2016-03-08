using System;
using System.Windows.Forms;

namespace Sudoku3000
{
    public partial class SettingsForm : Form
    {
        public SettingsForm()
        {
            InitializeComponent();
            switch (Program.size)
            {
                case 4: radioButton_4x4.Checked = true;
                        radioButton_9x9.Checked = false;
                        unfilledQuantityTrackBar.Maximum = 12;
                        break;
                case 9: radioButton_9x9.Checked = true;
                        radioButton_4x4.Checked = false;
                        unfilledQuantityTrackBar.Maximum = 53;
                        break;
            }
            unfilledQuantityTrackBar.Value = Program.unFilledCells;
            unfilledQuantitylabel.Text = Program.unFilledCells.ToString();
        }

        private void okButton_Click(object sender, EventArgs e)
        {
            Program.unFilledCells = unfilledQuantityTrackBar.Value;
            Program.size = radioButton_9x9.Checked ? 9 : 4;
            Program.blockSize = radioButton_9x9.Checked ? 3 : 2;
            this.Close();
        }

        private void cancelButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void unfilledQuantityTrackBar_MouseMove(object sender, MouseEventArgs e)
        {
            unfilledQuantitylabel.Text = unfilledQuantityTrackBar.Value.ToString();
        }

        private void radioButton_9x9_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton_9x9.Checked)
            {
                unfilledQuantityTrackBar.Maximum = 53;
                unfilledQuantityTrackBar.Value = 30;
                unfilledQuantitylabel.Text = "30";
            }
            else
            {
                unfilledQuantityTrackBar.Value = 6;
                unfilledQuantityTrackBar.Maximum = 12;
                unfilledQuantitylabel.Text = "6";
            }
        }
    }
}
