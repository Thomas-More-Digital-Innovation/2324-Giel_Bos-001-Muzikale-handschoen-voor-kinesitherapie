package fact.it.mvc.manageExSQ;


import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface ExerciseSequenceRepository extends JpaRepository<ExerciseSequence, Integer> {
    // You can add custom query methods here if needed
}