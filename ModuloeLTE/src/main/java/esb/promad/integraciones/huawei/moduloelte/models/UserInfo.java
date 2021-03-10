package esb.promad.integraciones.huawei.moduloelte.models;

public class UserInfo {

    protected String id;
    protected String category;
    protected String priority;
    protected String name;

    public UserInfo() {
    }

    public UserInfo(String id, String category, String priority, String name) {
        this.id = id;
        this.category = category;
        this.priority = priority;
        this.name = name;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getCategory() {
        return category;
    }

    public void setCategory(String category) {
        this.category = category;
    }

    public String getPriority() {
        return priority;
    }

    public void setPriority(String priority) {
        this.priority = priority;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return "UserInfo{" +
                "id='" + id + '\'' +
                ", category='" + category + '\'' +
                ", priority='" + priority + '\'' +
                ", name='" + name + '\'' +
                '}';
    }
}
