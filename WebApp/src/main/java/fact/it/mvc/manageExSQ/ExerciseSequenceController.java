package fact.it.mvc.manageExSQ;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;

import fact.it.mvc.ExSQList.ExerciseSequenceList;
import fact.it.mvc.ExSQList.ExerciseSequenceListService;
import fact.it.mvc.ManageEx.Exercise;
import fact.it.mvc.ManageEx.ExerciseService;



@Controller
public class ExerciseSequenceController {
    @Autowired
    private final ExerciseSequenceService exerciseSequenceService;
    private final ExerciseService exerciseService;
    private final ExerciseSequenceListService exerciseSequenceListService;

    public ExerciseSequenceController(ExerciseSequenceService exerciseSequenceService, ExerciseService exerciseService, ExerciseSequenceListService exerciseSequenceListService) {
        this.exerciseSequenceService = exerciseSequenceService;
        this.exerciseService = exerciseService;
        this.exerciseSequenceListService = exerciseSequenceListService;
    }

    @GetMapping("/manageExSQ")
    public String getAllExerciseSQs(Model model) {
        List<ExerciseSequence> sequences = exerciseSequenceService.getAllExerciseSequences();
        List<ExerciseSequenceList> sequenceLists = exerciseSequenceListService.getAllExerciseSequenceLists();
        List<Exercise> exercises = exerciseService.getAllExercises();
        model.addAttribute("sequences", sequences);
        model.addAttribute("sequenceLists", sequenceLists);
        model.addAttribute("exercises", exercises);
        return "manageExSQ";
    }

    @RequestMapping("/addExSQ")
    public String addExSQ(HttpServletRequest request, HttpServletResponse response, Model model) {
        String name = request.getParameter("name");
        String description = request.getParameter("description");

        ExerciseSequence exerciseSequence = new ExerciseSequence();

        exerciseSequence.setName(name);
        exerciseSequence.setDescription(description);

        int id = exerciseSequenceService.createExerciseSequence(exerciseSequence).getSequenceId();

        ExerciseSequence sequence = exerciseSequenceService.getExerciseSequenceById(id);
        List<Exercise> exercises = exerciseService.getAllExercises();
        model.addAttribute("sequence", sequence);
        model.addAttribute("exercises", exercises);
        return "manageExSQAdd";
    }
    @GetMapping("/editExToSQ/{id}")
    public String editExToSQ(@PathVariable("id") int id, Model model) {

        ExerciseSequence sequence = exerciseSequenceService.getExerciseSequenceById(id);
        List<Exercise> exercises = exerciseService.getAllExercises();
        List<ExerciseSequenceList> sequenceLists = exerciseSequenceListService.getExerciseBySQID(id);
        model.addAttribute("sequence", sequence);
        model.addAttribute("exercises", exercises);
        model.addAttribute("sequenceLists", sequenceLists);
        return "manageExSQAdd";
    }
    

    @RequestMapping("/addExToSQ/{id}")
    public String addExToSQ(@PathVariable("id") int id, HttpServletRequest request, HttpServletResponse response, Model model){
        int exSQID = id;
        int exID = Integer.parseInt(request.getParameter("ex"));

        ExerciseSequenceList newExerciseSequenceList = new ExerciseSequenceList();
        List<ExerciseSequenceList> sequenceLists = exerciseSequenceListService.getExerciseBySQID(exSQID);
        newExerciseSequenceList.setExID(exID);
        newExerciseSequenceList.setExSQID(exSQID);
        newExerciseSequenceList.setPlace(sequenceLists.size()-1);
        exerciseSequenceListService.createExerciseSequenceList(newExerciseSequenceList);

        List<Exercise> exercises = exerciseService.getAllExercises();
        ExerciseSequence sequence = exerciseSequenceService.getExerciseSequenceById(exSQID);
        sequenceLists = exerciseSequenceListService.getExerciseBySQID(exSQID);
        model.addAttribute("sequence", sequence);
        model.addAttribute("exercises", exercises);
        model.addAttribute("sequenceLists", sequenceLists);
        return "manageExSQAdd";
    }

    @GetMapping("/editExSQ/{id}")
    public String editExerciseSequenceForm(@PathVariable("id") int id, Model model) {
        ExerciseSequence sequence = exerciseSequenceService.getExerciseSequenceById(id);
        model.addAttribute("sequence", sequence);
        return "manageExSQEdit";
    }
    @RequestMapping("/updateExSQ/{id}")
    public String updateExSq(@PathVariable("id") int id, HttpServletRequest request, HttpServletResponse response) {
        String name = request.getParameter("name");
        String description = request.getParameter("description");

        ExerciseSequence exerciseSequence = exerciseSequenceService.getExerciseSequenceById(id);
        exerciseSequence.setName(name);
        exerciseSequence.setDescription(description);
        exerciseSequenceService.updateExerciseSequence(id, exerciseSequence);
        return "redirect:/manageExSQ";
    }

    @GetMapping("/deleteExSQ/{id}")
    public String deleteExercise(@PathVariable("id") int id) {
        exerciseSequenceService.deleteExerciseSequence(id);
        return "redirect:/manageExSQ";
    }
    @GetMapping("deleteEXSQList/{id}")
    public String deleteExSQList(@PathVariable("id") int id) {
        int exSQID = exerciseSequenceListService.getExerciseSequenceListById(id).getExSQID();
        exerciseSequenceListService.deleteExerciseSequenceList(id);

        return "redirect:/editExToSQ/" + exSQID;
    }
    
}