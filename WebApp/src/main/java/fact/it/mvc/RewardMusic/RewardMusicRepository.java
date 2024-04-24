package fact.it.mvc.RewardMusic;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface RewardMusicRepository extends JpaRepository<RewardMusic, Integer> {
    // You can add custom query methods here if needed
}