//import com.sun.org.apache.xml.internal.security.utils.HelperNodeList;

import java.util.concurrent.Semaphore;

public class Santa implements Runnable {

	enum SantaState {SLEEPING, READY_FOR_CHRISTMAS, WOKEN_UP_BY_ELVES, WOKEN_UP_BY_REINDEER};
	private SantaState state;
	private SantaScenario scenario;
	private boolean flag = true;//boolean
	private Semaphore semaphore;

	public Santa(SantaScenario scenario) {
		this.state = SantaState.SLEEPING;
		this.scenario = scenario;
	}

	public void kill()
	{
		flag = false;
		
	}
	
	public void wokeElves(Semaphore semaphore)
	{
		this.state = SantaState.WOKEN_UP_BY_ELVES;
		this.semaphore = semaphore;
	}

	
	
	
	@Override
	public void run() {
		while(flag) {
			// wait a day...
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				
				e.printStackTrace();
			}
			switch(state) {
			case SLEEPING: // if sleeping, continue to sleep
				break;
			case WOKEN_UP_BY_ELVES: 
	
				for(Elf elves: scenario.elves) {
					if (elves.getState() == Elf.ElfState.AT_SANTAS_DOOR && semaphore.availablePermits() != 3)
					{
						elves.setState(Elf.ElfState.WORKING);
						semaphore.release();
					}
				}
				this.state = SantaState.SLEEPING;
				break;
			case WOKEN_UP_BY_REINDEER: 
			
				break;
			case READY_FOR_CHRISTMAS: // nothing more to be done
				break;
			}
		}
	}

	
	/**
	 * Report about my state
	 */
	public void report() {
		System.out.println("Santa : " + state);
	}
	
	
}
