import java.util.Random;


public class Elf implements Runnable {

	

	enum ElfState {
		WORKING, TROUBLE, AT_SANTAS_DOOR
	};

	private ElfState state;
	/**
	 * The number associated with the Elf
	 */
	private int number;
	private Random rand = new Random();
	private SantaScenario scenario;
	private boolean flag = true;//boolean
	private int trouble;

	public void cont()
	{
		flag = true;
	}

	public void kill()
	{
		flag = false;
		
	}

	public Elf(int number, SantaScenario scenario) {
		this.number = number;
		this.scenario = scenario;
		this.state = ElfState.WORKING;
	}


	public ElfState getState() {
		return state;
	}

	/**
	 * Santa might call this function to fix the trouble
	 * @param state
	 */
	public void setState(ElfState state) {
		this.state = state;
	}


	@Override
	public void run() {
		while (flag) {
			trouble = 0;
      // wait a day
  		try {
  			Thread.sleep(100);
  		} catch (InterruptedException e) {
  			
  			e.printStackTrace();
  		}
			switch (this.state) {
			case WORKING: {
				// at each day, there is a 1% chance that an elf runs into
				// trouble.
				if (rand.nextDouble() < 0.01) {
					state = ElfState.TROUBLE;
				}
				break;
			}
			case TROUBLE:
				
			
				for(Elf elves: scenario.elves)
				{
					if (elves.getState() == ElfState.TROUBLE)
					{
						
						elves.kill();
						trouble++;
					}
				}
				//if three elves are in trouble, they go to Santa's door
				if (trouble == 3)
				{
					for(Elf elves: scenario.elves)
					{
						if (elves.getState() == ElfState.TROUBLE)
						{
							elves.setState(ElfState.AT_SANTAS_DOOR);

							elves.cont();
						}
					}
				}
				break;
			case AT_SANTAS_DOOR:
				
				scenario.santa.wokeElves();
				break;
			}
		}
	}

	/**
	 * Report about my state
	 */
	public void report() {
		System.out.println("Elf " + number + " : " + state);
	}

}
