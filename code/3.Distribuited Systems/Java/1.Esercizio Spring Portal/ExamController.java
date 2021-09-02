package portal;

import java.net.URI;
import java.net.URISyntaxException;
import java.util.List;
import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;


import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import javax.validation.Valid;
import portal.Exam;
import portal.ExamService;

@RestController
@RequestMapping("/api")
public class ExamController {
	@Autowired
	private ExamService examService;

	@GetMapping("/exams")
	public ResponseEntity<List<Exam>> getAllExams () {
		List<Exam> exams=examService.getAllExams();
		return ResponseEntity.ok().body(exams);
	}

	@PostMapping("/exams")
	public ResponseEntity<Exam> addExam (@Valid @RequestBody Exam e) throws URISyntaxException {
		if (e.getId()==null) {
			return ResponseEntity.badRequest().build();
		}
		Exam result = examService.addExam(e);
		return ResponseEntity.created(new URI ("/api/exams"+result.getId())).body(result);

	}

	@GetMapping("/exams/{id}")
	public ResponseEntity<Exam> getExam (@PathVariable Long id){
		Optional<Exam> exam = examService.getExam(id);
		if (exam.isPresent()) {
			return ResponseEntity.ok().body(exam.get());
		}
		return ResponseEntity.notFound().build();
	}

	@PutMapping("/exams")
	public ResponseEntity<Exam> updateExam (@Valid @RequestBody Exam e)  {
		if (e.getId()==null) {
			return ResponseEntity.badRequest().build();
		}
		Exam result = examService.updateExam(e);
		return ResponseEntity.ok().body(result);

	}

	@DeleteMapping ("/exams/{id}")
	public ResponseEntity<Void> deleteExam (@PathVariable Long id){
		if (!examService.getExam(id).isPresent()) {
			return ResponseEntity.notFound().build();
		}
		examService.deleteExam(id);
		return ResponseEntity.ok().build();
	}



}
