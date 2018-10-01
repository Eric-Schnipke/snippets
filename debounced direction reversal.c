/** @def   DMMP_ZERO_SPEED_THRESH
 *  @brief Zero speed threshold in m/s
 */
#define DMMP_ZERO_SPEED_THRESH (0.001f)

static boolean xfDirectionReversal(void)
{
    const float32_t krTruckSpeed = grTruckSpeed(); /* m/s */
    static float32_t srTruckSpeedLast = 0.000f;
    boolean fDirectionReversal = FALSE;

    /* srTruckSpeedLast will track krTruckSpeed when krTruckSpeed is outside of
    zero speed threshold but will stop when krTruckSpeed enters the zero speed
    threshold region.  Direction reversal is indicated depending upon which
    side of the zero speed threshold region krTruckSpeed re-emerges: If on the
    same side that it entered (as indicated by srTruckSpeedLast), then no
    direction reversal occurred; If on opposing sides, then a direction
    reversal occurred.  This algorithm is used to avoid truck speed
    oscillations near zero. */
    if( DMMP_ZERO_SPEED_THRESH < fabsf(krTruckSpeed) )
    {
        /* Direction reversal occurred if current and last truck speed are on opposing sides of zero speed threshold region */
        fDirectionReversal = (  ((krTruckSpeed >  DMMP_ZERO_SPEED_THRESH) && (srTruckSpeedLast < -DMMP_ZERO_SPEED_THRESH))
                             || ((krTruckSpeed < -DMMP_ZERO_SPEED_THRESH) && (srTruckSpeedLast >  DMMP_ZERO_SPEED_THRESH))
                             );
        srTruckSpeedLast = krTruckSpeed;
    }

    return fDirectionReversal;
}