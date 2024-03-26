package fact.it.mvc.User;

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
import fact.it.mvc.UserExerciseSequence.UserExcerciseSequence;
import fact.it.mvc.UserExerciseSequence.UserExcerciseSequenceService;
import fact.it.mvc.manageExSQ.ExerciseSequence;
import fact.it.mvc.manageExSQ.ExerciseSequenceService;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@Controller
public class UserController {
    @Autowired
    private final UserService userService;
    private final ExerciseSequenceService exerciseSequenceService;
    private final ExerciseService exerciseService;
    private final ExerciseSequenceListService exerciseSequenceListService;
    private final UserExcerciseSequenceService userExcerciseSequenceService;

    public UserController(UserService userService, ExerciseSequenceService exerciseSequenceService, ExerciseService exerciseService, ExerciseSequenceListService exerciseSequenceListService, UserExcerciseSequenceService userExcerciseSequenceService){
        this.userService = userService;
        this.exerciseSequenceService = exerciseSequenceService;
        this.exerciseService = exerciseService;
        this.exerciseSequenceListService = exerciseSequenceListService;
        this.userExcerciseSequenceService = userExcerciseSequenceService;
    }

    @GetMapping("/managePatients")
    public String getMethodName(Model model) {
        List<User> patients = userService.getAllUsers();
        model.addAttribute("patients", patients);
        return "managePatients";
    }

    @RequestMapping("/addPatient")
    public String addPatient(HttpServletRequest request, Model model) {
        String firstName = request.getParameter("firstName");
        String lastName = request.getParameter("lastName");

        User newUser = new User();
        newUser.setFirstName(firstName);
        newUser.setLastName(lastName);

        int userID = userService.createUser(newUser).getUserID();

        User patient = userService.getUserById(userID);
        List<ExerciseSequence> sequences = exerciseSequenceService.getAllExerciseSequences();
        List<ExerciseSequenceList> sequenceLists = exerciseSequenceListService.getAllExerciseSequenceLists();
        List<Exercise> exercises = exerciseService.getAllExercises();
        List<UserExcerciseSequence> userSequences = userExcerciseSequenceService.getAllByUserId(userID);
        model.addAttribute("patient", patient);
        model.addAttribute("sequences", sequences);
        model.addAttribute("sequenceLists", sequenceLists);
        model.addAttribute("exercises", exercises);
        model.addAttribute("userSequences", userSequences);

        return "managePatientsAdd";
    }

    @GetMapping("/editPatientToSQ/{id}")
    public String editPatientToSQ(@PathVariable("id") int id, Model model) {
        User patient = userService.getUserById(id);
        List<ExerciseSequence> sequences = exerciseSequenceService.getAllExerciseSequences();
        List<ExerciseSequenceList> sequenceLists = exerciseSequenceListService.getAllExerciseSequenceLists();
        List<Exercise> exercises = exerciseService.getAllExercises();
        List<UserExcerciseSequence> userSequences = userExcerciseSequenceService.getAllByUserId(id);
        model.addAttribute("patient", patient);
        model.addAttribute("sequences", sequences);
        model.addAttribute("sequenceLists", sequenceLists);
        model.addAttribute("exercises", exercises);
        model.addAttribute("userSequences", userSequences);

        return "managePatientsAdd";
    }
    

    @RequestMapping("/addPatientToSQ/{id}")
    public String addPatientToSQ(@PathVariable("id") int id, HttpServletRequest request, HttpServletResponse response, Model model){
        int userID = id;
        int exSQID = Integer.parseInt(request.getParameter("exSQID"));

        UserExcerciseSequence newUserExcerciseSequence = new UserExcerciseSequence();
        newUserExcerciseSequence.setUserID(userID);
        newUserExcerciseSequence.setExSQID(exSQID);

        userExcerciseSequenceService.createUserExerciseSequence(newUserExcerciseSequence);

        User patient = userService.getUserById(userID);
        List<ExerciseSequence> sequences = exerciseSequenceService.getAllExerciseSequences();
        List<ExerciseSequenceList> sequenceLists = exerciseSequenceListService.getAllExerciseSequenceLists();
        List<Exercise> exercises = exerciseService.getAllExercises();
        List<UserExcerciseSequence> userSequences = userExcerciseSequenceService.getAllByUserId(userID);
        model.addAttribute("patient", patient);
        model.addAttribute("sequences", sequences);
        model.addAttribute("sequenceLists", sequenceLists);
        model.addAttribute("exercises", exercises);
        model.addAttribute("userSequences", userSequences);

        return "managePatientsAdd";
    }

    @GetMapping("/editPatient/{id}")
    public String editPatient(@PathVariable("id") int id, Model model) {
        User user = userService.getUserById(id);
        model.addAttribute("patient", user);
        return "managePatientsEdit";
    }

    @RequestMapping("/updatePatient/{id}")
    public String updatePatient(@PathVariable("id") int id, HttpServletRequest request, HttpServletResponse response) {
        String firstName = request.getParameter("firstName");
        String lastName = request.getParameter("lastName");

        User updatUser = userService.getUserById(id);
        updatUser.setFirstName(firstName);
        updatUser.setLastName(lastName);

        userService.createUser(updatUser);
        return "redirect:/managePatients";
    }

    @GetMapping("/deletePatient/{id}")
    public String deletePatient(@PathVariable("id") int id){
        userService.deleteUser(id);
        return "redirect:/managePatients";
    }

    @GetMapping("/deleteUserSequence/{userID}/{exSQID}")
    public String deleteUserSequence(@PathVariable("userID") int userID, @PathVariable("exSQID") int exSQID) {
        userExcerciseSequenceService.deleteUserExerciseSequence(userID, exSQID);
        return "redirect:/editPatientToSQ/" + userID;
    }
}
