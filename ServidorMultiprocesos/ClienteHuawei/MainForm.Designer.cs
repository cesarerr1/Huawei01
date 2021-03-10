namespace ClienteHuawei
{
    partial class MainForm
    {
        /// <summary>
        /// Variable del diseñador necesaria.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén usando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben desechar; false en caso contrario.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido de este método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            this.tabOperaciones = new System.Windows.Forms.TabControl();
            this.pageTelefonia = new System.Windows.Forms.TabPage();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.buttonColgar = new System.Windows.Forms.Button();
            this.buttonDescolgar = new System.Windows.Forms.Button();
            this.buttonLlamar = new System.Windows.Forms.Button();
            this.textBoxLlamada = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.buttonCSInactiva = new System.Windows.Forms.Button();
            this.buttonCSActiva = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.buttonAsociar = new System.Windows.Forms.Button();
            this.textExtension = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.textIDAgente = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.pageRadios = new System.Windows.Forms.TabPage();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.principalToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.configuraciónToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ayudaToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.acercaDeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.statusSistema = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusConexion = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripProgressBarConexion = new System.Windows.Forms.ToolStripProgressBar();
            this.textBitacora = new System.Windows.Forms.TextBox();
            this.tabOperaciones.SuspendLayout();
            this.pageTelefonia.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.statusSistema.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabOperaciones
            // 
            this.tabOperaciones.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tabOperaciones.Controls.Add(this.pageTelefonia);
            this.tabOperaciones.Controls.Add(this.pageRadios);
            this.tabOperaciones.Location = new System.Drawing.Point(12, 27);
            this.tabOperaciones.Name = "tabOperaciones";
            this.tabOperaciones.SelectedIndex = 0;
            this.tabOperaciones.Size = new System.Drawing.Size(619, 186);
            this.tabOperaciones.TabIndex = 1;
            // 
            // pageTelefonia
            // 
            this.pageTelefonia.Controls.Add(this.groupBox2);
            this.pageTelefonia.Controls.Add(this.groupBox1);
            this.pageTelefonia.Location = new System.Drawing.Point(4, 22);
            this.pageTelefonia.Name = "pageTelefonia";
            this.pageTelefonia.Padding = new System.Windows.Forms.Padding(3);
            this.pageTelefonia.Size = new System.Drawing.Size(611, 160);
            this.pageTelefonia.TabIndex = 0;
            this.pageTelefonia.Text = "Telefonía";
            this.pageTelefonia.UseVisualStyleBackColor = true;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.buttonColgar);
            this.groupBox2.Controls.Add(this.buttonDescolgar);
            this.groupBox2.Controls.Add(this.buttonLlamar);
            this.groupBox2.Controls.Add(this.textBoxLlamada);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.buttonCSInactiva);
            this.groupBox2.Controls.Add(this.buttonCSActiva);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Location = new System.Drawing.Point(7, 65);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(598, 91);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Operación telefonista";
            // 
            // buttonColgar
            // 
            this.buttonColgar.Enabled = false;
            this.buttonColgar.Location = new System.Drawing.Point(315, 59);
            this.buttonColgar.Name = "buttonColgar";
            this.buttonColgar.Size = new System.Drawing.Size(75, 23);
            this.buttonColgar.TabIndex = 5;
            this.buttonColgar.Text = "Colgar";
            this.buttonColgar.UseVisualStyleBackColor = true;
            this.buttonColgar.Click += new System.EventHandler(this.OnButtonColgar);
            // 
            // buttonDescolgar
            // 
            this.buttonDescolgar.Enabled = false;
            this.buttonDescolgar.Location = new System.Drawing.Point(214, 59);
            this.buttonDescolgar.Name = "buttonDescolgar";
            this.buttonDescolgar.Size = new System.Drawing.Size(75, 23);
            this.buttonDescolgar.TabIndex = 5;
            this.buttonDescolgar.Text = "Descolgar";
            this.buttonDescolgar.UseVisualStyleBackColor = true;
            this.buttonDescolgar.Click += new System.EventHandler(this.OnButtonDescolgar);
            // 
            // buttonLlamar
            // 
            this.buttonLlamar.Enabled = false;
            this.buttonLlamar.Location = new System.Drawing.Point(517, 22);
            this.buttonLlamar.Name = "buttonLlamar";
            this.buttonLlamar.Size = new System.Drawing.Size(75, 23);
            this.buttonLlamar.TabIndex = 4;
            this.buttonLlamar.Text = "Llamar";
            this.buttonLlamar.UseVisualStyleBackColor = true;
            this.buttonLlamar.Click += new System.EventHandler(this.OnButtonLlamar);
            // 
            // textBoxLlamada
            // 
            this.textBoxLlamada.Location = new System.Drawing.Point(411, 24);
            this.textBoxLlamada.Name = "textBoxLlamada";
            this.textBoxLlamada.ReadOnly = true;
            this.textBoxLlamada.Size = new System.Drawing.Size(100, 20);
            this.textBoxLlamada.TabIndex = 3;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(355, 27);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(50, 13);
            this.label4.TabIndex = 2;
            this.label4.Text = "Llamada:";
            // 
            // buttonCSInactiva
            // 
            this.buttonCSInactiva.Enabled = false;
            this.buttonCSInactiva.Location = new System.Drawing.Point(182, 22);
            this.buttonCSInactiva.Name = "buttonCSInactiva";
            this.buttonCSInactiva.Size = new System.Drawing.Size(75, 23);
            this.buttonCSInactiva.TabIndex = 1;
            this.buttonCSInactiva.Text = "Inactiva";
            this.buttonCSInactiva.UseVisualStyleBackColor = true;
            this.buttonCSInactiva.Click += new System.EventHandler(this.OnButtonSTInactiva);
            // 
            // buttonCSActiva
            // 
            this.buttonCSActiva.Enabled = false;
            this.buttonCSActiva.Location = new System.Drawing.Point(101, 22);
            this.buttonCSActiva.Name = "buttonCSActiva";
            this.buttonCSActiva.Size = new System.Drawing.Size(75, 23);
            this.buttonCSActiva.TabIndex = 1;
            this.buttonCSActiva.Text = "Activa";
            this.buttonCSActiva.UseVisualStyleBackColor = true;
            this.buttonCSActiva.Click += new System.EventHandler(this.OnButtonSTActiva);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 27);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(92, 13);
            this.label3.TabIndex = 0;
            this.label3.Text = "Status Operación:";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.buttonAsociar);
            this.groupBox1.Controls.Add(this.textExtension);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.textIDAgente);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(7, 7);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(598, 52);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Datos del agente";
            // 
            // buttonAsociar
            // 
            this.buttonAsociar.Location = new System.Drawing.Point(415, 18);
            this.buttonAsociar.Name = "buttonAsociar";
            this.buttonAsociar.Size = new System.Drawing.Size(132, 23);
            this.buttonAsociar.TabIndex = 2;
            this.buttonAsociar.Text = "Asociar Agente";
            this.buttonAsociar.UseVisualStyleBackColor = true;
            this.buttonAsociar.Click += new System.EventHandler(this.OnButtonAsociar);
            // 
            // textExtension
            // 
            this.textExtension.Location = new System.Drawing.Point(290, 20);
            this.textExtension.MaxLength = 10;
            this.textExtension.Name = "textExtension";
            this.textExtension.Size = new System.Drawing.Size(100, 20);
            this.textExtension.TabIndex = 1;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(228, 23);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(56, 13);
            this.label2.TabIndex = 0;
            this.label2.Text = "Extensión:";
            // 
            // textIDAgente
            // 
            this.textIDAgente.Location = new System.Drawing.Point(114, 20);
            this.textIDAgente.MaxLength = 10;
            this.textIDAgente.Name = "textIDAgente";
            this.textIDAgente.Size = new System.Drawing.Size(100, 20);
            this.textIDAgente.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(44, 23);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(64, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "No. Agente:";
            // 
            // pageRadios
            // 
            this.pageRadios.Location = new System.Drawing.Point(4, 22);
            this.pageRadios.Name = "pageRadios";
            this.pageRadios.Padding = new System.Windows.Forms.Padding(3);
            this.pageRadios.Size = new System.Drawing.Size(611, 160);
            this.pageRadios.TabIndex = 1;
            this.pageRadios.Text = "Radios";
            this.pageRadios.UseVisualStyleBackColor = true;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.principalToolStripMenuItem,
            this.ayudaToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(643, 24);
            this.menuStrip1.TabIndex = 2;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // principalToolStripMenuItem
            // 
            this.principalToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.configuraciónToolStripMenuItem});
            this.principalToolStripMenuItem.Name = "principalToolStripMenuItem";
            this.principalToolStripMenuItem.Size = new System.Drawing.Size(65, 20);
            this.principalToolStripMenuItem.Text = "Principal";
            // 
            // configuraciónToolStripMenuItem
            // 
            this.configuraciónToolStripMenuItem.Name = "configuraciónToolStripMenuItem";
            this.configuraciónToolStripMenuItem.Size = new System.Drawing.Size(150, 22);
            this.configuraciónToolStripMenuItem.Text = "Configuración";
            this.configuraciónToolStripMenuItem.Click += new System.EventHandler(this.OnMenuConfiguracion);
            // 
            // ayudaToolStripMenuItem
            // 
            this.ayudaToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.acercaDeToolStripMenuItem});
            this.ayudaToolStripMenuItem.Name = "ayudaToolStripMenuItem";
            this.ayudaToolStripMenuItem.Size = new System.Drawing.Size(53, 20);
            this.ayudaToolStripMenuItem.Text = "Ayuda";
            // 
            // acercaDeToolStripMenuItem
            // 
            this.acercaDeToolStripMenuItem.Name = "acercaDeToolStripMenuItem";
            this.acercaDeToolStripMenuItem.Size = new System.Drawing.Size(138, 22);
            this.acercaDeToolStripMenuItem.Text = "Acerca de ...";
            // 
            // statusSistema
            // 
            this.statusSistema.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusConexion,
            this.toolStripProgressBarConexion});
            this.statusSistema.Location = new System.Drawing.Point(0, 347);
            this.statusSistema.Name = "statusSistema";
            this.statusSistema.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.statusSistema.Size = new System.Drawing.Size(643, 22);
            this.statusSistema.TabIndex = 3;
            this.statusSistema.Text = "statusStrip1";
            // 
            // toolStripStatusConexion
            // 
            this.toolStripStatusConexion.Name = "toolStripStatusConexion";
            this.toolStripStatusConexion.Size = new System.Drawing.Size(526, 17);
            this.toolStripStatusConexion.Spring = true;
            this.toolStripStatusConexion.Text = "Datos de conexión";
            this.toolStripStatusConexion.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // toolStripProgressBarConexion
            // 
            this.toolStripProgressBarConexion.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.toolStripProgressBarConexion.Name = "toolStripProgressBarConexion";
            this.toolStripProgressBarConexion.Size = new System.Drawing.Size(100, 16);
            // 
            // textBitacora
            // 
            this.textBitacora.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBitacora.BackColor = System.Drawing.Color.Bisque;
            this.textBitacora.Location = new System.Drawing.Point(12, 219);
            this.textBitacora.Multiline = true;
            this.textBitacora.Name = "textBitacora";
            this.textBitacora.ReadOnly = true;
            this.textBitacora.Size = new System.Drawing.Size(619, 125);
            this.textBitacora.TabIndex = 4;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(643, 369);
            this.Controls.Add(this.textBitacora);
            this.Controls.Add(this.statusSistema);
            this.Controls.Add(this.tabOperaciones);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainForm";
            this.Text = "Modulo de integración PROMAD - IPCC";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.OnDialogoLeave);
            this.tabOperaciones.ResumeLayout(false);
            this.pageTelefonia.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.statusSistema.ResumeLayout(false);
            this.statusSistema.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TabControl tabOperaciones;
        private System.Windows.Forms.TabPage pageTelefonia;
        private System.Windows.Forms.TabPage pageRadios;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem principalToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem configuraciónToolStripMenuItem;
        private System.Windows.Forms.StatusStrip statusSistema;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusConexion;
        private System.Windows.Forms.ToolStripProgressBar toolStripProgressBarConexion;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox textIDAgente;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button buttonAsociar;
        private System.Windows.Forms.TextBox textExtension;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ToolStripMenuItem ayudaToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem acercaDeToolStripMenuItem;
        private System.Windows.Forms.TextBox textBitacora;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button buttonColgar;
        private System.Windows.Forms.Button buttonDescolgar;
        private System.Windows.Forms.Button buttonLlamar;
        private System.Windows.Forms.TextBox textBoxLlamada;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button buttonCSInactiva;
        private System.Windows.Forms.Button buttonCSActiva;
        private System.Windows.Forms.Label label3;
    }
}

