TARGET = firstExamples.alt

SOURCE_ALT = Minimal.alt\
	FIFO_V1.alt\
	FIFO_V2.alt\
	Switch.alt\
	Generator.alt\
	Lamplight.alt\
	CircuitV1.alt\
	CircuitV2.alt\
	CircuitV1_OK.alt\
	PoolOfJobs.alt\
	SchedulerRandom.alt\
	SchedulerPriority.alt\
	Scheduler.alt\
	Teacher.alt\
	Student.alt\
	LessonDifficult.alt\
	LessonUnpleasant.alt\
	LessonPriority.alt\
	Lesson.alt\
	Domain.alt\
	Comment.alt\
	Initial.alt\

DIFF_ALT = Circuit-correction.diff

all: $(TARGET) $(DIFF_ALT)

$(TARGET) :  $(SOURCE_ALT)
	rm -f $(TARGET)
	for d in $(SOURCE_ALT); do \
		cat $$d >> $(TARGET);\
	done

$(DIFF_ALT) : $(SOURCE_ALT)
	diff -n CircuitV1.alt CircuitV1_OK.alt > Circuit-correction.diff || true

clean:
	rm -f *~

cleanAll : clean
	rm -f $(TARGET) $(DIFF_ALT)
