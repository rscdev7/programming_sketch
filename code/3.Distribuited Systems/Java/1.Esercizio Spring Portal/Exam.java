package portal;
import java.util.Date;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;


@Entity
public class Exam {
	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private Long id;
	@NotBlank
	private String description;
	@NotNull
	private Date date;

	public Exam () {
	}

	public Exam (String description,Date date) {
		this.description=description;
		this.date=date;
	}
	public Long getId () {
		return this.id;
	}

	public String get () {
		return this.description;
	}
}
