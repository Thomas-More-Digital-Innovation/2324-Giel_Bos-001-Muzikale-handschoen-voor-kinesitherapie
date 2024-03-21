package fact.it.mvc.RewardLEDRing;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface RewardLEDRingRepository extends JpaRepository<RewardLEDRing, Integer> {

    // You can define custom query methods here if needed
}
