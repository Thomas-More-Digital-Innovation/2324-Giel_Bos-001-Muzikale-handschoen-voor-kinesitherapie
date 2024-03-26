package fact.it.mvc.ManageEx;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.util.List;

import javax.servlet.http.HttpServletRequest;

import java.io.File;

import javax.servlet.http.HttpServletResponse;


@Controller
public class ExerciseController {
    @Autowired
    private final ExerciseService exerciseService;

    public ExerciseController(ExerciseService exerciseService) {
        this.exerciseService = exerciseService;
    }

    @GetMapping("/manageEx")
    public String getAllExercises(Model model) {
        List<Exercise> exercises = exerciseService.getAllExercises();
        model.addAttribute("exercises", exercises);
        return "manageEx";
    }

    private static final String UPLOAD_DIRECTORY = "/Users/Matt/Matt gesynchroniseerd/PlatformIO/Projects/2324-Giel_Bos-001-Muzikale-handschoen-voor-kinesitherapie/WebApp/src/main/resources/static/img";

    @RequestMapping("/addEx")
    public String addExercise(@RequestParam("picture") MultipartFile file, HttpServletRequest request, HttpServletResponse response) {
        String name = request.getParameter("name");
        String description = request.getParameter("description");
        String fileName = null;
        String exString = "";

        if (!file.isEmpty()) {
            try {
                fileName = file.getOriginalFilename();
                // Ensure unique file name
                System.out.println(UPLOAD_DIRECTORY + File.separator + fileName);
                file.transferTo(new File(UPLOAD_DIRECTORY + File.separator + fileName));
                System.out.println(UPLOAD_DIRECTORY);
                System.out.println(File.separator);
                System.out.println(fileName);
            } catch (Exception ex) {
                // Handle file upload exception
                // You might want to log the exception
                ex.printStackTrace(); // Log the exception
                return "error"; // Or redirect to an error page
            }
        } else {
            System.out.println("no file found");
            // Handle case when no file is uploaded
            return "error"; // Or redirect to an error page
            
        }

        String exerciseKind = request.getParameter("typeEX");
        if(exerciseKind.equals("p")){
            exString = exerciseKind;
        }
        else{
            String palm = request.getParameter("handpalm");
            String thumb = request.getParameter("thumb");
            String fingers = request.getParameter("fingers");

            if((palm == "0,-1,0" ) && (thumb != "0,0,0")){
                String[] parts = thumb.split(",");
                StringBuilder output = new StringBuilder();
                for (String part : parts) {
                    int value = Integer.parseInt(part);
                    output.append(Math.abs(value)).append(",");
                }
                output.deleteCharAt(output.length() - 1);

                thumb = output.toString();           
            }

            if((palm == "0,0,-1") && (fingers != "0,0,0")){
                String[] parts = fingers.split(",");
                StringBuilder output = new StringBuilder();
                for (String part : parts) {
                    int value = Integer.parseInt(part);
                    output.append(Math.abs(value)).append(",");
                }
                output.deleteCharAt(output.length() - 1);

                fingers = output.toString();
            }
            exString = palm + ";" + thumb + ";" + fingers;
        }
        Exercise exercise = new Exercise();
        exercise.setName(name);
        exercise.setPicture("/img" + File.separator + fileName);
        exercise.setDescription(description);
        exercise.setExString(exString);

        try {
            exerciseService.createExercise(exercise);
            return "redirect:/manageEx";
        } catch (Exception ex) {
            // Rollback the file upload if exercise creation fails
            new File(UPLOAD_DIRECTORY + File.separator + fileName).delete();
            ex.printStackTrace(); // Log the exception
            return "error"; // Or redirect to an error page
        }
    }

    @GetMapping("/editEx/{id}")
    public String editExerciseForm(@PathVariable("id") int id, Model model) {
        Exercise exercise = exerciseService.getExerciseById(id);
        model.addAttribute("exercise", exercise);
        return "manageExEdit";
    }

    @RequestMapping("/updateEx/{id}")
    public String updateEx(@PathVariable("id") int id,@RequestParam("picture") MultipartFile file, HttpServletRequest request, HttpServletResponse response) {
        String name = request.getParameter("name");
        String description = request.getParameter("description");
        String fileName = null;
        String exString = "";

        System.out.println("Done step 1");

        if (!file.isEmpty()) {
            System.out.println("DoneStep2");
            try {
                fileName = file.getOriginalFilename();
                System.out.println(UPLOAD_DIRECTORY + File.separator + fileName);
                file.transferTo(new File(UPLOAD_DIRECTORY + File.separator + fileName));
                System.out.println(UPLOAD_DIRECTORY);
                System.out.println(File.separator);
                System.out.println(fileName);
            } catch (Exception ex) {
                System.out.println("in catch");
                // Handle file upload exception
                // You might want to log the exception
                ex.printStackTrace(); // Log the exception
                return "error"; // Or redirect to an error page
            }
        } else {
            System.out.println("no file found");
            // Handle case when no file is uploaded
            return "error"; // Or redirect to an error page
            
        }

        String exerciseKind = request.getParameter("typeEX");

        if(exerciseKind == "p"){
            exString = exerciseKind;
        }
        else{
            String palm = request.getParameter("handpalm");
            String thumb = request.getParameter("thumb");
            String fingers = request.getParameter("fingers");

            if((palm == "0,-1,0" ) && (thumb != "0,0,0")){
                String[] parts = thumb.split(",");
                StringBuilder output = new StringBuilder();
                for (String part : parts) {
                    int value = Integer.parseInt(part);
                    output.append(Math.abs(value)).append(",");
                }
                output.deleteCharAt(output.length() - 1);

                thumb = output.toString();           
            }

            if((palm == "0,0,-1") && (fingers != "0,0,0")){
                String[] parts = fingers.split(",");
                StringBuilder output = new StringBuilder();
                for (String part : parts) {
                    int value = Integer.parseInt(part);
                    output.append(Math.abs(value)).append(",");
                }
                output.deleteCharAt(output.length() - 1);

                fingers = output.toString();
            }
            exString = palm + ";" + thumb + ";" + fingers;
        }

        Exercise exercise = exerciseService.getExerciseById(id);
        exercise.setName(name);
        exercise.setPicture("/img" + File.separator + fileName);
        exercise.setDescription(description);
        exercise.setExString(exString);

        try {
            exerciseService.createExercise(exercise);
            return "redirect:/manageEx";
        } catch (Exception ex) {
            // Rollback the file upload if exercise creation fails
            new File(UPLOAD_DIRECTORY + File.separator + fileName).delete();
            ex.printStackTrace(); // Log the exception
            return "error"; // Or redirect to an error page
        }
    }

    @GetMapping("/deleteEx/{id}")
    public String deleteExercise(@PathVariable("id") int id) {
        exerciseService.deleteExercise(id);
        return "redirect:/manageEx";
    }
}