package fact.it.mvc.RewardMusic;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import java.util.List;

@Service
public class RewardMusicService {
    @Autowired
    private final RewardMusicRepository rewardMusicRepository;

    public RewardMusicService(RewardMusicRepository rewardMusicRepository) {
        this.rewardMusicRepository = rewardMusicRepository;
    }

    public List<RewardMusic> getAllRewardMusic() {
        return rewardMusicRepository.findAll();
    }

    public RewardMusic getRewardMusicById(int id) {
        return rewardMusicRepository.findById(id).orElse(null);
    }

    public RewardMusic saveRewardMusic(RewardMusic rewardMusic) {
        return rewardMusicRepository.save(rewardMusic);
    }

    public void deleteRewardMusicById(int id) {
        rewardMusicRepository.deleteById(id);
    }

    // You can add more service methods as per your application requirements
}