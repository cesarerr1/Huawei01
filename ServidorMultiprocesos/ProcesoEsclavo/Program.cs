using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using NLog;
using ProcesoEsclavo.Huawei;

namespace ProcesoEsclavo
{
    static class Program
    {
        static Logger logger = LogManager.GetCurrentClassLogger();

        /// <summary>
        /// Punto de entrada principal para la aplicación.
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            //Application.EnableVisualStyles();
            //Application.SetCompatibleTextRenderingDefault(false);
            //Application.Run(new Form1());
            logger.Trace("Inicio de la aplicación esclavo.");
            for (int cont = 0; cont < args.Length; cont++)
                logger.Trace("Item de configuracion[{0}]: {1}", cont, args[cont]);
            Application.Run(new ProcesoHuawei(args[0]));
        }
    }
}
