package fact.it.mvc.RewardLEDRing;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;

@Service
public class RewardLEDRingService {
    @Autowired
    private final RewardLEDRingRepository rewardLEDRingRepository;

    public RewardLEDRingService(RewardLEDRingRepository rewardLEDRingRepository) {
        this.rewardLEDRingRepository = rewardLEDRingRepository;
    }

    public RewardLEDRing saveRewardLEDRing(RewardLEDRing rewardLEDRing) {
        return rewardLEDRingRepository.save(rewardLEDRing);
    }

    public List<RewardLEDRing> getAllRewardLEDRings() {
        return rewardLEDRingRepository.findAll();
    }

    public RewardLEDRing getRewardLEDRingById(int id) {
        return rewardLEDRingRepository.findById(id).orElse(null);
    }

    public RewardLEDRing updateRewardLEDRing(int id, RewardLEDRing updatedRewardLEDRing) {
        if (rewardLEDRingRepository.existsById(id)) {
            updatedRewardLEDRing.setRwLEDRingID(id);
            return rewardLEDRingRepository.save(updatedRewardLEDRing);
        }
        return null; // or throw an exception as per your application logic
    }

    public void deleteRewardLEDRingById(int id) {
        rewardLEDRingRepository.deleteById(id);
    }

    public List<String> getAllHexCodes(RewardLEDRing rewardLEDRing){
        List<String> hexCodes = new ArrayList<>();
        hexCodes.add(rewardLEDRing.getHexCode0());
        hexCodes.add(rewardLEDRing.getHexCode1());
        hexCodes.add(rewardLEDRing.getHexCode2());
        hexCodes.add(rewardLEDRing.getHexCode3());
        hexCodes.add(rewardLEDRing.getHexCode4());
        hexCodes.add(rewardLEDRing.getHexCode5());
        hexCodes.add(rewardLEDRing.getHexCode6());
        hexCodes.add(rewardLEDRing.getHexCode7());
        hexCodes.add(rewardLEDRing.getHexCode8());
        hexCodes.add(rewardLEDRing.getHexCode9());
        hexCodes.add(rewardLEDRing.getHexCode10());
        hexCodes.add(rewardLEDRing.getHexCode11());
        return hexCodes;
    }
}
