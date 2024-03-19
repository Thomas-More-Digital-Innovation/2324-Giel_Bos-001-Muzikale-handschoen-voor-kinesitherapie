package fact.it.mvc.UserExerciseSequence;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import java.util.List;
import java.util.Optional;

@Service
public class UserExcerciseSequenceService {

    @Autowired
    private UserExcerciseSequenceRepository userExcerciseSequenceRepository;

    public List<UserExcerciseSequence> getAllByUserId(int userID) {
        return userExcerciseSequenceRepository.findAllByUserID(userID);
    }

    public List<UserExcerciseSequence> getAllUserExerciseSequences() {
        return userExcerciseSequenceRepository.findAll();
    }

    public Optional<UserExcerciseSequence> getUserExerciseSequenceById(int userID, int exSQID) {
        return userExcerciseSequenceRepository.findById(new UserExcerciseSequenceId(userID, exSQID));
    }

    public UserExcerciseSequence createUserExerciseSequence(UserExcerciseSequence userExerciseSequence) {
        return userExcerciseSequenceRepository.save(userExerciseSequence);
    }

    public void updateUserExerciseSequence(UserExcerciseSequence userExerciseSequence) {
        userExcerciseSequenceRepository.save(userExerciseSequence);
    }

    public void deleteUserExerciseSequence(int userID, int exSQID) {
        userExcerciseSequenceRepository.deleteById(new UserExcerciseSequenceId(userID, exSQID));
    }
}
