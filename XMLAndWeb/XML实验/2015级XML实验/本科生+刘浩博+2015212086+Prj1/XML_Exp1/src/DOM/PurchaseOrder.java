package DOM;

//该对象是一个实体bean，其字段信息对应xml文件中的元素字段
public class PurchaseOrder {
    private String comp_name;

    @Override
    public String toString() {
        return "comp_name="+comp_name;
    }

    public String getComp_name() {
        return comp_name;
    }

    public void setComp_name(String comp_name) {
        this.comp_name = comp_name;
    }
}
