package fact.it.mvc.ExSQList;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

import java.util.Collections;
import java.util.Comparator;

@Service
public class ExerciseSequenceListService {

    @Autowired
    private ExerciseSequenceListRepository repository;

    public List<ExerciseSequenceList> getAllExerciseSequenceLists() {
        return repository.findAll();
    }

    public ExerciseSequenceList getExerciseSequenceListById(int id) {
        return repository.findById(id).orElse(null);
    }

    public ExerciseSequenceList createExerciseSequenceList(ExerciseSequenceList exerciseSequenceList) {

        return repository.save(exerciseSequenceList);
    }

    public void deleteExerciseSequenceList(int id) {
        repository.deleteById(id);
    }
    public List<ExerciseSequenceList> getExerciseBySQID(int exSQID){
        List<ExerciseSequenceList> exerciseList = repository.findByExSQID(exSQID);
        Collections.sort(exerciseList, Comparator.comparingInt(ExerciseSequenceList::getPlace));
        return exerciseList;
    }
}
