using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ClienteHuawei;
using NLog;

namespace ClienteHuawei
{
    public partial class ConfiguracionForm : Form
    {
        protected Logger logger = LogManager.GetCurrentClassLogger();
        public Dictionary<DatosConexion, string> datosConexion;
        ArchivoConfiguracion configuracion;

        public ConfiguracionForm(Dictionary<DatosConexion, string> datosConexion,
            ArchivoConfiguracion configuracion)
        {
            InitializeComponent();

            // Se cargan los valores de la conexión
            textMainIPCC.Text = datosConexion[DatosConexion.mainIPCC];
            textBkIPCC.Text = datosConexion[DatosConexion.backupIPCC];
            textTimeOut.Text = datosConexion[DatosConexion.timeOut];
            textMainIPCCWS.Text = datosConexion[DatosConexion.webServiceURL];
            textBkIPCCWS.Text = datosConexion[DatosConexion.backupServiceURL];
            textAccessCode1.Text = datosConexion[DatosConexion.accessCode1];
            textAccessCode2.Text = datosConexion[DatosConexion.accessCode2];
            textTransferAccessCode.Text = datosConexion[DatosConexion.transferCode];
            textOutBoundPrefix.Text = datosConexion[DatosConexion.outboundPrefix];
            textExtensionPrefix.Text = datosConexion[DatosConexion.extensionPrefix];
            textExtnesionLength.Text = datosConexion[DatosConexion.extensionLenght];

            // Se cargan los datos de conexión con Promad
            textURLPromad.Text = datosConexion[DatosConexion.urlPromad];
            textTimeoutPromad.Text = datosConexion[DatosConexion.timeOutPromad];

            buttonAceptar.Enabled = false;
            this.datosConexion = datosConexion;
            this.configuracion = configuracion;
        }

        private void OnButtonAceptar(object sender, EventArgs e)
        {
            try
            {
                buttonAceptar.Enabled = false;

                // Se edita la información del canal obtenido
                datosConexion[DatosConexion.mainIPCC] = textMainIPCC.Text;
                datosConexion[DatosConexion.backupIPCC]= textBkIPCC.Text;
                datosConexion[DatosConexion.timeOut] = textTimeOut.Text;
                datosConexion[DatosConexion.webServiceURL] = textMainIPCCWS.Text;
                datosConexion[DatosConexion.backupServiceURL] = textBkIPCCWS.Text;
                datosConexion[DatosConexion.accessCode1] = textAccessCode1.Text;
                datosConexion[DatosConexion.accessCode2] = textAccessCode2.Text;
                datosConexion[DatosConexion.transferCode] = textTransferAccessCode.Text;
                datosConexion[DatosConexion.outboundPrefix] = textOutBoundPrefix.Text;
                datosConexion[DatosConexion.extensionPrefix] = textExtensionPrefix.Text;
                datosConexion[DatosConexion.extensionLenght] = textExtnesionLength.Text;

                datosConexion[DatosConexion.urlPromad] = textURLPromad.Text;
                datosConexion[DatosConexion.timeOutPromad] = textTimeoutPromad.Text;

                // Se actualiza el archivo de configuración
                if (configuracion.ActualizarArchivoConfiguracion(datosConexion) != 0)
                    MessageBox.Show("Error en la actualización del archivo de configuración." +
                        configuracion.errMsg, "Actualizando configuración.",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);

                this.Close();
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en la edición de la configuración. {0}",
                    ex.Message, ex);
            }
        }

        private void OnButtonCancelar(object sender, EventArgs e)
        {
            try
            {
                this.Close();
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en la carga de los datos previos de configuracion. {0}",
                    ex.Message, ex);
            }
        }

        private void OnFieldDirty(object sender, EventArgs e)
        {
            try
            {
                buttonAceptar.Enabled = true;
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el procesamiento de edición de un campo. {0}",
                    ex.Message, ex);
            }
        }

        private void OnCierreConfiguracion(object sender, FormClosedEventArgs e)
        {
            try
            {
                logger.Trace("Se detecto el cierre del dialogo.");
                buttonAceptar.Enabled = false;

                // Se cargan los valores de la conexión
                textMainIPCC.Text = datosConexion[DatosConexion.mainIPCC];
                textBkIPCC.Text = datosConexion[DatosConexion.backupIPCC];
                textTimeOut.Text = datosConexion[DatosConexion.timeOut];
                textMainIPCCWS.Text = datosConexion[DatosConexion.webServiceURL];
                textBkIPCCWS.Text = datosConexion[DatosConexion.backupServiceURL];
                textAccessCode1.Text = datosConexion[DatosConexion.accessCode1];
                textAccessCode2.Text = datosConexion[DatosConexion.accessCode2];
                textTransferAccessCode.Text = datosConexion[DatosConexion.transferCode];
                textOutBoundPrefix.Text = datosConexion[DatosConexion.outboundPrefix];
                textExtensionPrefix.Text = datosConexion[DatosConexion.extensionPrefix];
                textExtnesionLength.Text = datosConexion[DatosConexion.extensionLenght];

                textURLPromad.Text = datosConexion[DatosConexion.urlPromad];
                textTimeoutPromad.Text = datosConexion[DatosConexion.timeOutPromad];
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                logger.Error("Error en el procedimiento de cierre del dialogo de configuracion. {0}",
                    ex.Message, ex);
            }
        }
    }
}
