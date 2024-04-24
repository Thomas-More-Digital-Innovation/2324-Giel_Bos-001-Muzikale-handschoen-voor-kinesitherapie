package fact.it.mvc.ExSQList;

import java.util.List;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface ExerciseSequenceListRepository extends JpaRepository<ExerciseSequenceList, Integer> {
    List<ExerciseSequenceList> findByExSQID(int exSQID);

}