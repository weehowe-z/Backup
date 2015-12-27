package Test;

public class RecordString implements Record{
	public String value = null;
	
	public RecordString(String value){
		this.value = value;
	}
	
	public String getValue() {
		return value;
	}
	
}
