package esb.promad.integraciones.huawei.moduloelte.config;

import org.springframework.context.annotation.Configuration;
import springfox.documentation.builders.ApiInfoBuilder;
import static springfox.documentation.builders.PathSelectors.regex;
import springfox.documentation.builders.RequestHandlerSelectors;
import springfox.documentation.service.ApiInfo;
import springfox.documentation.service.Contact;
import springfox.documentation.spi.DocumentationType;
import springfox.documentation.spring.web.plugins.Docket;
import springfox.documentation.swagger2.annotations.EnableSwagger2;

@Configuration
@EnableSwagger2
public class SwaggerConfig {

    public Docket productApp() {
        return new Docket(DocumentationType.SWAGGER_2)
                .select()
                .apis(RequestHandlerSelectors.basePackage("esb.promad.integraciones.huawei.moduloelte.api"))
                .paths(regex("/api.*"))
                .build()
                .apiInfo(metaInfo());
    }

    private ApiInfo metaInfo() {

        return new ApiInfoBuilder()
                .title("API de para radios Huawei eLTE/Promad")
                .description("Módulo que permite integrar los distintos tipos de radios de Huawei al ESB de Promad.")
                .version("1.0")
                .contact(new Contact(
                        "Alejandro Torres",
                        "http://www.promad.com.mx",
                        "atorres@promad.com.mx"))
                .build();
    }
}
