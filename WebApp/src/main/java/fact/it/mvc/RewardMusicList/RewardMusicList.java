package fact.it.mvc.RewardMusicList;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Table;

import javax.persistence.Id;
import javax.persistence.Column;

import lombok.Data;

@Entity
@Data
@Table(name = "ExerciseSequenceList")
public class RewardMusicList {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "rwMListID")
    private int rwMListID;
    
    @Column(name = "rwMID")
    private int rwMID;
    
    @Column(name = "noteID")
    private int noteID;

    @Column(name = "place")
    private int place;
}