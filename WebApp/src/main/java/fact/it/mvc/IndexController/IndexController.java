package fact.it.mvc.IndexController;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

import fact.it.mvc.ExSQList.ExerciseSequenceList;
import fact.it.mvc.ExSQList.ExerciseSequenceListService;
import fact.it.mvc.ManageEx.Exercise;
import fact.it.mvc.ManageEx.ExerciseService;
import fact.it.mvc.User.User;
import fact.it.mvc.User.UserService;
import fact.it.mvc.UserExerciseSequence.UserExcerciseSequence;
import fact.it.mvc.UserExerciseSequence.UserExcerciseSequenceService;
import fact.it.mvc.manageExSQ.ExerciseSequence;
import fact.it.mvc.manageExSQ.ExerciseSequenceService;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class IndexController {
    @Autowired
    private final ExerciseSequenceService exerciseSequenceService;
    private final ExerciseService exerciseService;
    private final ExerciseSequenceListService exerciseSequenceListService;
    private final UserService userService;
    private final UserExcerciseSequenceService userExcerciseSequenceService;

    public IndexController(ExerciseSequenceService exerciseSequenceService, ExerciseService exerciseService, ExerciseSequenceListService exerciseSequenceListService, UserService userService, UserExcerciseSequenceService userExcerciseSequenceService) {
        this.exerciseSequenceService = exerciseSequenceService;
        this.exerciseService = exerciseService;
        this.exerciseSequenceListService = exerciseSequenceListService;
        this.userService = userService;
        this.userExcerciseSequenceService = userExcerciseSequenceService;
    }

    @GetMapping("/")
    public String getAllExerciseSQs(Model model) {
        List<ExerciseSequence> sequences = exerciseSequenceService.getAllExerciseSequences();
        List<ExerciseSequenceList> sequenceLists = exerciseSequenceListService.getAllExerciseSequenceLists();
        List<Exercise> exercises = exerciseService.getAllExercises();
        List<User> patients = userService.getAllUsers();
        model.addAttribute("sequences", sequences);
        model.addAttribute("sequenceLists", sequenceLists);
        model.addAttribute("exercises", exercises);
        model.addAttribute("patients", patients);
        return "index";
    }
    @RequestMapping("/filterPatient")
    public String filterPatient(HttpServletRequest request, HttpServletResponse response, Model model) {
        String patient = request.getParameter("patient");

        if(patient.equals("All")){
            List<ExerciseSequence> sequences = exerciseSequenceService.getAllExerciseSequences();
            List<ExerciseSequenceList> sequenceLists = exerciseSequenceListService.getAllExerciseSequenceLists();
            List<Exercise> exercises = exerciseService.getAllExercises();
            List<User> patients = userService.getAllUsers();
            model.addAttribute("sequences", sequences);
            model.addAttribute("sequenceLists", sequenceLists);
            model.addAttribute("exercises", exercises);
            model.addAttribute("patients", patients);
        }
        else{
            int patientID = Integer.parseInt(patient);
            List<UserExcerciseSequence> userSequences = userExcerciseSequenceService.getAllByUserId(patientID);
            List<ExerciseSequence> sequences = exerciseSequenceService.getExerciseSequencesByUser(userSequences);
            List<ExerciseSequenceList> sequenceLists = exerciseSequenceListService.getAllExerciseSequenceLists();
            List<Exercise> exercises = exerciseService.getAllExercises();
            List<User> patients = userService.getAllUsers();
            model.addAttribute("sequences", sequences);
            model.addAttribute("sequenceLists", sequenceLists);
            model.addAttribute("exercises", exercises);
            model.addAttribute("patients", patients);
        }
        return "index";
    }
}
