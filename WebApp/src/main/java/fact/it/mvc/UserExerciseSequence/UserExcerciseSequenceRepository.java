package fact.it.mvc.UserExerciseSequence;

import org.springframework.data.jpa.repository.JpaRepository;
import java.util.List;

public interface UserExcerciseSequenceRepository extends JpaRepository<UserExcerciseSequence, UserExcerciseSequenceId> {
    List<UserExcerciseSequence> findAllByUserID(int userID);
}