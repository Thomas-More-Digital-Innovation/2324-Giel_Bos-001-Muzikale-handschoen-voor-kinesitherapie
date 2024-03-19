package fact.it.mvc.ManageEx;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class ExerciseService {
    @Autowired
    private final ExerciseRepository exerciseRepository;

    public ExerciseService(ExerciseRepository exerciseRepository) {
        this.exerciseRepository = exerciseRepository;
    }

    public List<Exercise> getAllExercises() {
        return exerciseRepository.findAll();
    }

    public Exercise getExerciseById(int id) {
        return exerciseRepository.findById(id).orElse(null);
    }

    public Exercise createExercise(Exercise exercise) {
        return exerciseRepository.save(exercise);
    }

    public Exercise updateExercise(int id, Exercise updatedExercise) {
        if (!exerciseRepository.existsById(id)) {
            return null;
        }
        updatedExercise.setExID(id); // Ensure the ID is set correctly
        return exerciseRepository.save(updatedExercise);
    }

    public void deleteExercise(int id) {
        exerciseRepository.deleteById(id);
    }
}