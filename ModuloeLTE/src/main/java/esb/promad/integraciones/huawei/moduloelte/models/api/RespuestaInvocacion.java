package esb.promad.integraciones.huawei.moduloelte.models.api;

import io.swagger.annotations.ApiModelProperty;

public class RespuestaInvocacion {

    @ApiModelProperty(required = true, notes = "Código de error de la respuesta.")
    private int errCode;
    @ApiModelProperty (required = true, notes = "Mensaje de error asociado a la operación.")
    private String errMsg;

    public RespuestaInvocacion(int errCode, String errMsg) {
        this.errCode = errCode;
        this.errMsg = errMsg;
    }

    public int getErrCode() {
        return errCode;
    }

    public void setErrCode(int errCode) {
        this.errCode = errCode;
    }

    public String getErrMsg() {
        return errMsg;
    }

    public void setErrMsg(String errMsg) {
        this.errMsg = errMsg;
    }

    @Override
    public String toString() {
        return "RespuestaInvocacion{" +
                "errCode=" + errCode +
                ", errMsg='" + errMsg + '\'' +
                '}';
    }
}
