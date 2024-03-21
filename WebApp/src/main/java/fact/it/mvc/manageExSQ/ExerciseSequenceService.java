package fact.it.mvc.manageExSQ;

import java.util.ArrayList;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import fact.it.mvc.UserExerciseSequence.UserExcerciseSequence;

@Service
public class ExerciseSequenceService {
    @Autowired
    private final ExerciseSequenceRepository exerciseSequenceRepository;

    public ExerciseSequenceService(ExerciseSequenceRepository exerciseSequenceRepository) {
        this.exerciseSequenceRepository = exerciseSequenceRepository;
    }

    public List<ExerciseSequence> getAllExerciseSequences() {
        return exerciseSequenceRepository.findAll();
    }

    public ExerciseSequence getExerciseSequenceById(int id) {
        return exerciseSequenceRepository.findById(id).orElse(null);
    }

    public ExerciseSequence createExerciseSequence(ExerciseSequence exerciseSequence) {
        return exerciseSequenceRepository.save(exerciseSequence);
    }
    public int getExerciseSequenceId(ExerciseSequence exerciseSequence){

        return exerciseSequence.getSequenceId();
    }

    public ExerciseSequence updateExerciseSequence(int id, ExerciseSequence updatedExercise) {
        if (!exerciseSequenceRepository.existsById(id)) {
            return null;
        }
        updatedExercise.setExSQID(id); // Ensure the ID is set correctly
        return exerciseSequenceRepository.save(updatedExercise);
    }

    public void deleteExerciseSequence(int id) {
        exerciseSequenceRepository.deleteById(id);
    }

    public List<ExerciseSequence> getExerciseSequencesByUser(List<UserExcerciseSequence> userSequences){
        List<ExerciseSequence> exerciseSequences = new ArrayList<>();
        for(int i = 0; i < userSequences.size(); i++){
            exerciseSequences.add(exerciseSequenceRepository.getById(userSequences.get(i).getExQSID()));
        }
        return exerciseSequences;
    }
}
