namespace Sudoku3000
{
    partial class SettingsForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.sizeGroupBox = new System.Windows.Forms.GroupBox();
            this.radioButton_9x9 = new System.Windows.Forms.RadioButton();
            this.radioButton_4x4 = new System.Windows.Forms.RadioButton();
            this.unfilledGroupBox = new System.Windows.Forms.GroupBox();
            this.unfilledQuantitylabel = new System.Windows.Forms.Label();
            this.unfilledQuantityTrackBar = new System.Windows.Forms.TrackBar();
            this.okButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.sizeGroupBox.SuspendLayout();
            this.unfilledGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.unfilledQuantityTrackBar)).BeginInit();
            this.SuspendLayout();
            // 
            // sizeGroupBox
            // 
            this.sizeGroupBox.Controls.Add(this.radioButton_9x9);
            this.sizeGroupBox.Controls.Add(this.radioButton_4x4);
            this.sizeGroupBox.Location = new System.Drawing.Point(12, 12);
            this.sizeGroupBox.Name = "sizeGroupBox";
            this.sizeGroupBox.Size = new System.Drawing.Size(429, 83);
            this.sizeGroupBox.TabIndex = 0;
            this.sizeGroupBox.TabStop = false;
            this.sizeGroupBox.Text = "Size";
            // 
            // radioButton_9x9
            // 
            this.radioButton_9x9.AutoSize = true;
            this.radioButton_9x9.Location = new System.Drawing.Point(90, 37);
            this.radioButton_9x9.Name = "radioButton_9x9";
            this.radioButton_9x9.Size = new System.Drawing.Size(42, 17);
            this.radioButton_9x9.TabIndex = 1;
            this.radioButton_9x9.Text = "9x9";
            this.radioButton_9x9.UseVisualStyleBackColor = true;
            this.radioButton_9x9.CheckedChanged += new System.EventHandler(this.radioButton_9x9_CheckedChanged);
            // 
            // radioButton_4x4
            // 
            this.radioButton_4x4.AutoSize = true;
            this.radioButton_4x4.Location = new System.Drawing.Point(283, 37);
            this.radioButton_4x4.Name = "radioButton_4x4";
            this.radioButton_4x4.Size = new System.Drawing.Size(42, 17);
            this.radioButton_4x4.TabIndex = 0;
            this.radioButton_4x4.TabStop = true;
            this.radioButton_4x4.Text = "4x4";
            this.radioButton_4x4.UseVisualStyleBackColor = true;
            // 
            // unfilledGroupBox
            // 
            this.unfilledGroupBox.Controls.Add(this.unfilledQuantitylabel);
            this.unfilledGroupBox.Controls.Add(this.unfilledQuantityTrackBar);
            this.unfilledGroupBox.Location = new System.Drawing.Point(12, 115);
            this.unfilledGroupBox.Name = "unfilledGroupBox";
            this.unfilledGroupBox.Size = new System.Drawing.Size(429, 79);
            this.unfilledGroupBox.TabIndex = 1;
            this.unfilledGroupBox.TabStop = false;
            this.unfilledGroupBox.Text = "Numbers of unfilled cells";
            // 
            // unfilledQuantitylabel
            // 
            this.unfilledQuantitylabel.AutoSize = true;
            this.unfilledQuantitylabel.Location = new System.Drawing.Point(280, 37);
            this.unfilledQuantitylabel.Name = "unfilledQuantitylabel";
            this.unfilledQuantitylabel.Size = new System.Drawing.Size(13, 13);
            this.unfilledQuantitylabel.TabIndex = 1;
            this.unfilledQuantitylabel.Text = "0";
            // 
            // unfilledQuantityTrackBar
            // 
            this.unfilledQuantityTrackBar.Cursor = System.Windows.Forms.Cursors.Default;
            this.unfilledQuantityTrackBar.Location = new System.Drawing.Point(81, 31);
            this.unfilledQuantityTrackBar.Name = "unfilledQuantityTrackBar";
            this.unfilledQuantityTrackBar.Size = new System.Drawing.Size(160, 42);
            this.unfilledQuantityTrackBar.TabIndex = 0;
            this.unfilledQuantityTrackBar.MouseMove += new System.Windows.Forms.MouseEventHandler(this.unfilledQuantityTrackBar_MouseMove);
            // 
            // okButton
            // 
            this.okButton.Location = new System.Drawing.Point(12, 218);
            this.okButton.Name = "okButton";
            this.okButton.Size = new System.Drawing.Size(75, 23);
            this.okButton.TabIndex = 2;
            this.okButton.Text = "OK";
            this.okButton.UseVisualStyleBackColor = true;
            this.okButton.Click += new System.EventHandler(this.okButton_Click);
            // 
            // cancelButton
            // 
            this.cancelButton.Location = new System.Drawing.Point(102, 218);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(75, 23);
            this.cancelButton.TabIndex = 3;
            this.cancelButton.Text = "Cancel";
            this.cancelButton.UseVisualStyleBackColor = true;
            this.cancelButton.Click += new System.EventHandler(this.cancelButton_Click);
            // 
            // SettingsForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(454, 253);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.okButton);
            this.Controls.Add(this.unfilledGroupBox);
            this.Controls.Add(this.sizeGroupBox);
            this.Name = "SettingsForm";
            this.Text = "Settings";
            this.sizeGroupBox.ResumeLayout(false);
            this.sizeGroupBox.PerformLayout();
            this.unfilledGroupBox.ResumeLayout(false);
            this.unfilledGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.unfilledQuantityTrackBar)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox sizeGroupBox;
        private System.Windows.Forms.RadioButton radioButton_9x9;
        private System.Windows.Forms.RadioButton radioButton_4x4;
        private System.Windows.Forms.GroupBox unfilledGroupBox;
        private System.Windows.Forms.Label unfilledQuantitylabel;
        private System.Windows.Forms.TrackBar unfilledQuantityTrackBar;
        private System.Windows.Forms.Button okButton;
        private System.Windows.Forms.Button cancelButton;
    }
}