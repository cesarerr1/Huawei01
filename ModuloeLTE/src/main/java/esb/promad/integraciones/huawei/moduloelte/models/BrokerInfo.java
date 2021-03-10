package esb.promad.integraciones.huawei.moduloelte.models;

public class BrokerInfo {

    protected String broker;
    protected String status;
    protected String version;

    public BrokerInfo() {
    }

    public BrokerInfo(String broker, String status, String version) {
        this.broker = broker;
        this.status = status;
        this.version = version;
    }

    public String getBroker() {
        return broker;
    }

    public void setBroker(String broker) {
        this.broker = broker;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getVersion() {
        return version;
    }

    public void setVersion(String version) {
        this.version = version;
    }

    @Override
    public String toString() {
        return "BrokerInfo{" +
                "broker='" + broker + '\'' +
                ", status='" + status + '\'' +
                ", version='" + version + '\'' +
                '}';
    }
}
