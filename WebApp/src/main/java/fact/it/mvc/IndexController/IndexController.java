package fact.it.mvc.IndexController;
import java.util.ArrayList;
import java.util.List;
import java.util.Comparator;
import java.util.Map;
import java.util.stream.Collectors;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;

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
import fact.it.mvc.RewardLEDRing.RewardLEDRingService;
import fact.it.mvc.RewardLEDRing.RewardLEDRing;
import fact.it.mvc.RewardMusicList.RewardMusicListService;
import fact.it.mvc.RewardMusicList.RewardMusicList;
import fact.it.mvc.Note.NoteService;
import fact.it.mvc.Note.Note;
import org.springframework.web.bind.annotation.RequestMapping;


@Controller
public class IndexController {
    @Autowired
    private final ExerciseSequenceService exerciseSequenceService;
    private final ExerciseService exerciseService;
    private final ExerciseSequenceListService exerciseSequenceListService;
    private final UserService userService;
    private final UserExcerciseSequenceService userExcerciseSequenceService;
    private final RewardLEDRingService rewardLEDRingService;
    private final RewardMusicListService rewardMusicListService;
    private final NoteService noteService;

    public IndexController(ExerciseSequenceService exerciseSequenceService, 
    ExerciseService exerciseService, 
    ExerciseSequenceListService exerciseSequenceListService,
    UserService userService,
    UserExcerciseSequenceService userExcerciseSequenceService,
    RewardLEDRingService rewardLEDRingService,
    RewardMusicListService rewardMusicListService,
    NoteService noteService) {
        this.exerciseSequenceService = exerciseSequenceService;
        this.exerciseService = exerciseService;
        this.exerciseSequenceListService = exerciseSequenceListService;
        this.userService = userService;
        this.userExcerciseSequenceService = userExcerciseSequenceService;
        this.rewardLEDRingService = rewardLEDRingService;
        this.rewardMusicListService = rewardMusicListService;
        this.noteService = noteService;
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
    @GetMapping("/exec/{id}")
    public String exec(@PathVariable("id") int id, Model model) {
        ExerciseSequence sequence = exerciseSequenceService.getExerciseSequenceById(id);
        List<ExerciseSequenceList> sequenceList = exerciseSequenceListService.getExerciseBySQID(sequence.getExSQID());
        List<Exercise> exercises = exerciseService.getByList(sequenceList);
        List<String> exString = new ArrayList<>();
        List<String> name = new ArrayList<>();
        List<String> description = new ArrayList<>();
        List<String> picture = new ArrayList<>();
        for(int i=0; i< exercises.size(); i++){
            exString.add(exercises.get(i).getExString());
            name.add(exercises.get(i).getName());
            description.add(exercises.get(i).getDescription());
            picture.add(exercises.get(i).getPicture());
        }

        List<RewardLEDRing> rewardLEDRings = rewardLEDRingService.getAllRewardLEDRings();

        List<String> combinedHexCodesList = new ArrayList<>();

        for (int i = 0; i < rewardLEDRings.size(); i++) {
            RewardLEDRing rewardLEDRing = rewardLEDRings.get(i);

            StringBuilder combinedHexCodes = new StringBuilder();
            combinedHexCodes.append(rewardLEDRing.getHexCode0()).append(";")
                            .append(rewardLEDRing.getHexCode1()).append(";")
                            .append(rewardLEDRing.getHexCode2()).append(";")
                            .append(rewardLEDRing.getHexCode3()).append(";")
                            .append(rewardLEDRing.getHexCode4()).append(";")
                            .append(rewardLEDRing.getHexCode5()).append(";")
                            .append(rewardLEDRing.getHexCode6()).append(";")
                            .append(rewardLEDRing.getHexCode7()).append(";")
                            .append(rewardLEDRing.getHexCode8()).append(";")
                            .append(rewardLEDRing.getHexCode9()).append(";")
                            .append(rewardLEDRing.getHexCode10()).append(";")
                            .append(rewardLEDRing.getHexCode11());

            combinedHexCodesList.add(combinedHexCodes.toString());
        }

        List<RewardMusicList> rewardMusicLists = rewardMusicListService.getAllRewardMusicLists();

        Map<Integer, List<RewardMusicList>> musicListsByMusicId = rewardMusicLists.stream()
                .collect(Collectors.groupingBy(RewardMusicList::getRwMID));

        List<String> combinedNotesList = new ArrayList<>();

        for (Map.Entry<Integer, List<RewardMusicList>> entry : musicListsByMusicId.entrySet()) {

            List<RewardMusicList> musicLists = entry.getValue();


            List<RewardMusicList> sortedMusicLists = musicLists.stream()
                    .sorted(Comparator.comparingInt(RewardMusicList::getPlace))
                    .collect(Collectors.toList());

            StringBuilder combinedNotes = new StringBuilder();

            for (RewardMusicList musicList : sortedMusicLists) {
                Note note = noteService.getNoteById(musicList.getNoteID());
                int hzValue = note.getHzValue();

                combinedNotes.append(hzValue).append(";");
            }

            if (combinedNotes.length() > 0) {
                combinedNotes.deleteCharAt(combinedNotes.length() - 1);
            }

            combinedNotesList.add(combinedNotes.toString());
        }

        model.addAttribute("exStrings", exString);
        model.addAttribute("names", name);
        model.addAttribute("descriptions", description);
        model.addAttribute("pictures", picture);
        model.addAttribute("hexCodeList", combinedHexCodesList);
        model.addAttribute("musicList", combinedNotesList);
        return "execute";
    }
}