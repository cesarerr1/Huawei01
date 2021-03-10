package esb.promad.integraciones.huawei.moduloelte.models;

public class StatusInfo {

    protected String status;
    protected String errMsg;
    protected Integer errCode;

    public StatusInfo() {
    }

    public StatusInfo(String status, String errMsg, Integer errCode) {
        this.status = status;
        this.errMsg = errMsg;
        this.errCode = errCode;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getErrMsg() {
        return errMsg;
    }

    public void setErrMsg(String errMsg) {
        this.errMsg = errMsg;
    }

    public Integer getErrCode() {
        return errCode;
    }

    public void setErrCode(Integer errCode) {
        this.errCode = errCode;
    }

    @Override
    public String toString() {
        return "StatusInfo{" +
                "status='" + status + '\'' +
                ", errMsg='" + errMsg + '\'' +
                ", errCode=" + errCode +
                '}';
    }
}
