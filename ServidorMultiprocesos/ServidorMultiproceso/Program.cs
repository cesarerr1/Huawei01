using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NLog;

namespace ServidorMultiproceso
{
    class Program
    {
        static Logger logger = LogManager.GetCurrentClassLogger();

        static void Main(string[] args)
        {
            List<InterfaceHuawei> procesos = new List<InterfaceHuawei>();
            try
            {
                // Se generan los procesos
                logger.Trace("Intentando generar los procesos de soporte.");
                for (int i = 0; i < 2; i++)
                {
                    InterfaceHuawei temp = new InterfaceHuawei();
                    temp.Start("ClienteIPC" + i.ToString());
                    temp.InicializarDatosConexion("172.17.102.1", "", 9000, 
                        "https://172.17.102.2:8643/eds/services/ECUWebService",
                        "https://172.17.102.2:8643/eds/services/ECUWebService",
                        "90001", "90002", "", "", 8, "30007");
                    procesos.Add(temp);
                }

                Console.ReadLine();

                logger.Trace("Asociando los agentes.");
                procesos[0].AsociarAgente("108", "10008", "");

                Console.ReadLine();
                procesos[1].AsociarAgente("107", "10007", "");
                

                Console.ReadLine();

                // Se detienen los procesos
                logger.Trace("Cerrando los procesos de soporte.");
                foreach (InterfaceHuawei p in procesos)
                    p.Dispose();

                Console.ReadLine();
            }
            catch (Exception ex)
            {
                // Se detecto un error en el procedimiento
                System.Console.WriteLine("ERROR: " + ex.Message);
            }
        }
    }
}
