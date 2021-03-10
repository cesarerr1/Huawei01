package esb.promad.integraciones.huawei.moduloelte;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.builder.SpringApplicationBuilder;
import org.springframework.boot.web.support.SpringBootServletInitializer;

@SpringBootApplication
public class ModuloeLteApplication extends SpringBootServletInitializer {

	@Override
	protected SpringApplicationBuilder configure(SpringApplicationBuilder application) {
		return application.sources(ModuloeLteApplication.class);
	}

	public static void main(String[] args) {
		SpringApplication.run(ModuloeLteApplication.class, args);
	}
}
