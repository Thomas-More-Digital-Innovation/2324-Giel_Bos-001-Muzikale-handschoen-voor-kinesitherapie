package fact.it.mvc.Note;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.stereotype.Component;
@Component
public class NoteDataSeeder implements CommandLineRunner {
    @Autowired
    private final NoteRepository noteRepository;

    public NoteDataSeeder(NoteRepository noteRepository) {
        this.noteRepository = noteRepository;
    }

    @Override
    public void run(String... args) throws Exception {
        if (noteRepository.count() == 0) { // Check if the table is empty
            // Populate notes of the first octave
            String[] noteNames = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
            int baseHz = 261; // Assuming middle C (C4) is 261 Hz, adjust as needed
    
            for (int i = 0; i < noteNames.length; i++) {
                Note note = new Note();
                note.setNoteID(i + 1); // Assuming IDs start from 1
                note.setNote(noteNames[i]);
                int hzValue = (int) (baseHz * Math.pow(2, i / 12.0)); // Calculate Hz for each note and cast to int
                note.setHzValue(hzValue);
                noteRepository.save(note);
            }
        }
    }
}